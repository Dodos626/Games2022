#include "Player.h"

using json = nlohmann::json;

Player::Player(Point *spawn, int screen_width, int map_width, int screen_dx) {

	this->animator = new PlayerAnimator("Engine/Configs/PlayerAnimatorConfig.json", static_cast<int>(this->state));
	
	std::ifstream fin("Engine/Configs/PlayerConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	this->x = spawn->GetX();
	this->y = spawn->GetY();


	auto stats = data["stats"];
	
	this->health = stats["health"];
	this->attack_power = stats["attack_power"];
	this->armor = stats["armor"];
	this->mana = stats["mana"];
	this->lifes = stats["lifes"];
	this->points = stats["points"];


	auto physics = data["physics"];
	this->fall_speed = physics["fall_speed"];
	this->jump_speed = physics["jump_speed"];
	this->jump_height = physics["jump_height"];
	this->speed = physics["speed"];

	
	this->max_moving_x = map_width - screen_width + screen_dx;
	this->camera_dx = screen_dx;
	this->duck = false;
	this->height = 32;

	//initiate spell book
	this->spell_book = Spell_Book();
	this->spell_book.registerSpell(new Spell(48, std::bind(&Player::spellJump, this), std::bind(&Player::counterSpellJump, this)));

	//initiate spells
}

//MISC
void Player::TakeDamage(int damage) {
	if (this->armor - damage > 0) { // armor perisoteri tu damage
		this->armor -= damage;
	}
	else {
		this->health -= damage - this->armor; // health = health + armor - damage
		this->armor = 0; // midenizei to armor
	}
}

void Player::Render(double curr_time) {
	int x = this->x - this->GetCameraX();
	if (this->x > this->max_moving_x)
		x += this->x - this->max_moving_x;
	
	this->animator->render(x, this->y, curr_time, static_cast<int>(this->state));

	this->spell_book.checkIfSpellsEnded(curr_time);
	
	
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


void Player::spellJump() {
	this->jump_height *= 2;
}

void Player::counterSpellJump() {
	this->jump_height /= 2;
}