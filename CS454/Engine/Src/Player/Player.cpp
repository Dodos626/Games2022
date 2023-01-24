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
	this->lifes = stats["lifes"];
	this->points = stats["points"];

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

	//initiate spell book and spells
	this->CreateSpellBook();
	this->on_last_frame = false;
}

void Player::LoadStats(int map_width, int map_height, int y_offset) {
	this->stats_display = new DisplayStats(*this, map_width, map_height, y_offset);
}

//MISC
void Player::TakeDamage(int damage) {
	
	this->health -= damage/ this->damage_reduction;
}

void Player::Render(double curr_time) {
	int x = this->x - this->GetCameraX();
	if (this->x > this->max_moving_x)
		x += this->x - this->max_moving_x;
	al_draw_rectangle(x, this->y, x + 16, this->y + 32, al_map_rgb(150, 0, 0), 0);
	
	if (!this->is_attacking) //if not attacking simple render
		this->animator->render(x, this->y, curr_time, static_cast<int>(this->state));
	else // if attacking
	{
		// render attack returns 
		// 0 = 1st frame of the attack
		// 1 = second frame and last frame
		// 2 = ended
		int tmp = this->animator->renderAttack(x, this->y, curr_time, static_cast<int>(this->state), this->on_last_frame);
		std::cout << "tmp: " << tmp << std::endl;
		if (tmp == 2) {
			std::cout << "stop attacking \n ";
			this->on_last_frame = false; //reset
			this->is_attacking = false;  // not attacking 
			this->setStateWithDirection(p_state::idle_left); // dont care state
		}
		else if (tmp == 1) {
			this->on_last_frame = true;
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
	this->x = p->GetX();
	this->y = p->GetY();
}

void Player::Stand() {
	if (!this->duck)
		return;
	this->setStateWithDirection(p_state::idle_left);
	//this->y = y - 16;
	//this->height *= 2;
	this->duck = false;
}

void Player::Duck() {
	if (this->duck)
		return;
	this->setStateWithDirection(p_state::crouch_left);
	//this->y = y + 16;
	//this->height /= 2;
	this->duck = true;
}
void Player::ChangeStance() {
	if (this->duck)
		this->Stand();
	else
		this->Duck();
}

void Player::AnimateMoveLeft() {
	if (this->duck) 
		this->setState(p_state::crouch_left);
	else
		this->setState(p_state::move_left);
}

void Player::MoveLeft() {
	if (this->duck) 
		return;
	this->x -= this->speed;
}

void Player::AnimateMoveRight() {
	if (this->duck) {
		this->setState(p_state::crouch_right);
		return;
	}
	this->setState(p_state::move_right);
}

void Player::MoveRight() { 
	if (this->duck) {
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

	if (this->is_attacking) return; //can't attack if already attacking

	if (this->state != p_state::crouch_left && this->state != p_state::crouch_right) // if not crouching
		this->setStateWithDirection(p_state::atck_left); // standing attack
	else
		this->setStateWithDirection(p_state::crouch_atck_left); // else crouch attack
	
	this->animator->changeAnimation(static_cast<int>(this->state)); // change animation
	
	this->is_attacking = true; // set attacking to true
	this->on_last_frame = false; // we are on the first frame of the attack
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
	std::cout << "this was called \n";
	this->lifes += 3;
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

void Player::LoadStats() {
	this->stats_display->PrepareStats();
};