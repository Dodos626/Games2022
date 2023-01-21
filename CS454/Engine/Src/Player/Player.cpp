#include "Player.h"

using json = nlohmann::json;

Player::Player(Point *spawn, int screen_width, int map_width, int screen_dx) {

	this->animator = new PlayerAnimator("Engine/Configs/PlayerAnimatorConfig.json", static_cast<int>(this->state));
	
	std::ifstream fin("Engine/Configs/PlayerConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	this->x = spawn->GetX();
	this->y = spawn->GetY();
	this->health = data["health"];
	this->attack_power = data["attack_power"];
	this->armor = data["armor"];
	this->speed = data["speed"];
	this->max_moving_x = map_width - screen_width + screen_dx;
	this->camera_dx = screen_dx;
	this->duck = false;
	this->height = 32;
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
	this->y = y - 16;
	this->height *= 2;
	this->duck = false;
}

void Player::Duck() {
	if (this->duck)
		return;
	this->y = y + 16;
	this->height /= 2;
	this->duck = true;
}
void Player::ChangeStance() {
	if (this->duck)
		this->Stand();
	else
		this->Duck();
}
void Player::MoveLeft() { 
	if (this->duck)
		return;
	this->x -= this->speed;
}

void Player::MoveRight() { 
	if (this->duck)
		return;
	this->x += this->speed; 
}

void Player::MoveUp() { 
	this->Stand();
	this->y -= this->speed; 
}
