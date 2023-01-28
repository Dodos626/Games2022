#include "Player.h"

using json = nlohmann::json;

Player::Player(Point* spawn, int screen_width, int map_width, int screen_dx) {

	std::vector<std::string> animation_names;
	
	for (int i = 0; i < static_cast<int>(p_state::victory_pose) + 1; i++) {
		animation_names.push_back(p_stateToStr(static_cast<p_state>(i)));
	}

	this->animator = new PlayerAnimator("Engine/Configs/PlayerAnimatorConfig.json", static_cast<int>(this->state), animation_names);
	
	std::ifstream fin("Engine/Configs/PlayerConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	this->x = spawn->GetX();
	this->y = spawn->GetY();


	auto stats = data["stats"];
	
	this->health = this->max_health = stats["health"];
	this->attack_power = stats["attack_power"];
	this->mana = this->max_mana = stats["mana"];
	this->lives = stats["lives"];
	this->points = stats["points"];
	this->damage_reduction = 1;

	this->point_penalty = data["death"]["point_penalty"];

	this->stats_display = NULL;


	auto physics = data["physics"];
	this->fall_speed = physics["fall_speed"];
	this->jump_speed = physics["jump_speed"];
	this->jump_height = physics["jump_height"];
	this->speed = physics["speed"];

	
	this->max_moving_x = map_width - screen_width + screen_dx;
	this->camera_dx = screen_dx;
	this->duck = false;
	this->height = 32;
	this->width = 16;
	this->keys = 0;
	this->is_dead = false;

	//initiate spell book and spells
	this->CreateSpellBook();
}

void Player::LoadStats(int map_width, int map_height, int y_offset) {
	this->stats_display = new DisplayStats(*this, map_width, map_height, y_offset);
}

//MISC
void Player::TakeDamage(int damage, Point point_of_attack) {
	if (this->is_damaged || !this->isAlive()) return;

	if (this->state == p_state::crouch_left && point_of_attack.GetX() < this->x) { // an skibume kai koitame aristera

	}
	else if (this->state == p_state::crouch_right && point_of_attack.GetX() > this->x) { // an skivume kai koitame deksia

	}
	else {
		this->health -= damage / this->damage_reduction;
		if (this->health <= 0) {
			this->health = 0;

			this->lives -= 1;
			// Death Animation here
		}
		
	}

	if (this->is_attacking) {
		this->animator->StartForcedAnimation(0);
		this->is_attacking = false;
		this->setStateWithDirection(p_state::idle_left);
	}
	this->point_of_attack = point_of_attack;
	this->is_damaged = true;
	this->immunity = 0.5;
	// animate taking damage
}


void Player::RespawnFromDeath() {
	if (this->lives > 0) {
		this->health = this->max_health;
		this->mana = this->max_mana;
		this->points -= this->point_penalty;
	}
	else {
		this->health = 1;
		this->mana = 1;
		this->is_dead = true;
		// Lose game here
	}
}

void Player::RegenerateMana(int mana_gain) { 
	this->mana = (this->mana + mana_gain <= this->max_mana) ? this->health + mana_gain : this->max_mana; 
	// animate mana gain
}
void Player::RegenerateHealth(int hp_gain) {
	this->health = (this->health + hp_gain <= this->max_health) ? this->health + hp_gain : this->max_health;
	// animate hp gain
}

void Player::IncreaseLives(int difference) {
	this->lives += difference;
	// animate life gain
}

void Player::IncreasePoints(int points) {
	this->points += points;
}

void Player::IncreaseKeys(int keys) {
	this->keys += keys;
}

void Player::Render(double curr_time) {
	int x = this->x - this->GetCameraX();
	if (this->x > this->max_moving_x)
		x += this->x - this->max_moving_x;
	if (this->toggle_collision_box)
		al_draw_rectangle(x, this->y, x + 16, this->y + 32, al_map_rgb(150, 0, 0), 0);

	if (!this->is_attacking && !this->is_damaged) //if not attacking simple render
		this->animator->render(x, this->y, curr_time, static_cast<int>(this->state));
	else if (this->is_damaged && !this->is_attacking) {
		this->immunity -= curr_time;

		if (this->point_of_attack.GetX() > this->x && this->immunity > 0.25 && this->x > 1) { // deksia koituse o link
			this->MoveUp();
			this->MoveLeft();

		}
		else if (this->immunity > 0.25) {
			this->MoveUp();
			this->MoveRight();
		}
		this->animator->render(x, this->y, curr_time, static_cast<int>(this->state));
		if (this->immunity <= 0) { // taking damage ended
			this->is_damaged = false;
			this->immunity = 0;

		}
	}
	else // if attacking
	{
		bool flag = false;
		if (this->state == p_state::atck_left || this->state == p_state::crouch_atck_left) {
			flag = this->animator->renderWholeAnimationWithFixFrame(x, this->y, curr_time, -16, 0, 1 + this->cancelled_attack_offset);
		}
		else if (this->state == p_state::atck_right) {
			flag = this->animator->renderWholeAnimationWithFixFrame(x, this->y, curr_time, -16, 0, 2 + this->cancelled_attack_offset);
		}
		else {
			flag = this->animator->renderWholeAnimationWithFixFrame(x, this->y, curr_time, 0, 0, 0);
		}



		if (flag) {
			this->cancelled_attack_offset = 0;
			this->is_attacking = false;
			if (this->duck)
				this->setStateWithDirection(p_state::crouch_left);
			else
				this->setStateWithDirection(p_state::idle_left);
		}



	}
	if (this->stats_display)
		this->stats_display->Render();
}



int Player::GetCameraX(){
	if (this->x < this->camera_dx)
		return 0;
	else
		return this->x - this->camera_dx;
	
}

void Player::Respawn(Point *p) {
	if (!this->isAlive())
		this->RespawnFromDeath();
	this->x = p->GetX();
	this->y = p->GetY();
}

void Player::Stand() {
	if (!this->duck || this->is_attacking)
		return;
	this->setStateWithDirection(p_state::idle_left);
	//this->y = y - 16;
	//this->height *= 2;
	this->duck = false;
}

void Player::Duck() {
	if (this->duck || this->is_attacking)
		return;
	this->setStateWithDirection(p_state::crouch_left);
	//this->y = y + 16;
	//this->height /= 2;
	this->duck = true;
}
void Player::ChangeStance() {
	if (this->is_attacking)
		return;
	if (this->duck)
		this->Stand();
	else
		this->Duck();
}

void Player::AnimateMoveLeft() {
	if (this->duck || this->is_attacking)
		this->setState(p_state::crouch_left);
	else
		this->setState(p_state::move_left);
}


void Player::AnimateMoveRight() {
	if (this->duck || this->is_attacking) {
		this->setState(p_state::crouch_right);
		return;
	}
	this->setState(p_state::move_right);
}

void Player::MoveLeft() {
	if (this->duck || this->is_attacking)
		return;
	this->x -= this->speed;
}

void Player::MoveRight() { 
	if (this->duck || this->is_attacking) {
		return;
	}
	this->x += this->speed; 
}

void Player::MoveUp() { 
	this->Stand();
	setStateWithDirection(p_state::jump_left);
	this->y -= this->speed; 
}

void Player::MoveDown() {
	this->setStateWithDirection(p_state::land_left);
	this->y += this->speed; 
}

void Player::StopMoving() {
	if(this->state != p_state::crouch_left && this->state != p_state::crouch_right)
		this->setStateWithDirection(p_state::idle_left);
}

void Player::Attack() {

	if (this->is_attacking || this->is_damaged) return; //can't attack if already attacking

	if (this->state != p_state::crouch_left && this->state != p_state::crouch_right) // if not crouching
	{
		this->setStateWithDirection(p_state::atck_left); // standing attack
		this->animator->StartForcedAnimation(2); //set the numbers of forced frames
	}
	else
	{
		this->setStateWithDirection(p_state::crouch_atck_left); // else crouch attack
		this->animator->StartForcedAnimation(1); //set the numbers of forced frames
	}
	
	this->animator->changeAnimation(static_cast<int>(this->state)); // force change animation
	
	this->is_attacking = true; // set attacking to true
}

void Player::CancelledAttack() {
	if (this->is_attacking || this->is_damaged) return; //can't attack if already attacking

	if (this->state != p_state::crouch_left && this->state != p_state::crouch_right) // if not crouching
	{
		this->setStateWithDirection(p_state::atck_left); // standing attack
		this->animator->StartForcedAnimation(1); //set the numbers of forced frames
		this->animator->changeAnimation(static_cast<int>(this->state)); // force change animation
		this->is_attacking = true; // set attacking to true
		this->cancelled_attack_offset = -1;
	}

	
}

Point Player::GetAttackPoint() {
	int x = this->x;
	int y = this->y;
	if (static_cast<int>(this->state) % 2 == 0) { // if on left move
		x -= 16;
	}
	else {

		x += 31; 
	}
	if (this->duck) {
		y += 16; // y = 0 is top y = max_y is bottom
	}
	return Point(x, y);
}


//SPELL SECTION

void Player::CreateSpellBook(void) {
	this->spell_book = Spell_Book();
	this->spell_book.registerSpell(new Spell(32, std::bind(&Player::spellShield, this), std::bind(&Player::counterSpellShield, this), false));
	this->spell_book.registerSpell(new Spell(48, std::bind(&Player::spellJump, this), std::bind(&Player::counterSpellJump, this), false));
	this->spell_book.registerSpell(new Spell(70, std::bind(&Player::spellLife, this), nullptr, true));
	this->spell_book.registerSpell(new Spell(80, std::bind(&Player::spellFairy, this), std::bind(&Player::counterSpellFairy, this), false));
}

//spell shield => link takes half damage
void Player::spellShield() {
	this->damage_reduction = 2;
}
void Player::counterSpellShield() {
	this->damage_reduction = 1;
}


//spell jump => doubles the jump height
void Player::spellJump() {
	this->jump_height *= 2;
}
void Player::counterSpellJump() {
	this->jump_height /= 2;
}

//spell life => heals 3 life
void Player::spellLife() {
	this->lives += 3;
}

//spell fairy => Allows you to reach high places and cross lengthy gaps.
void Player::spellFairy() {
	this->jump_speed -= 1;
	this->fall_speed -= 1;
}

void Player::counterSpellFairy() {
	this->jump_speed += 1;
	this->fall_speed += 1;
}


// DISPLAY STATS SECTION
void Player::LoadStats() {
	this->stats_display->PrepareStats();
};