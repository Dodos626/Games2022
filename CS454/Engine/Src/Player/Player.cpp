#include "Player.h"

using json = nlohmann::json;

Player::Player(int x, int y, int screen_width, int map_width, int screen_dx) {
	
	std::ifstream fin("Engine/Configs/PlayerConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	this->x = x;
	this->y = y;
	this->health = data["health"];
	this->attack_power = data["attack_power"];
	this->armor = data["armor"];
	this->speed = data["speed"];
	this->max_moving_x = map_width - screen_width + screen_dx;
	this->camera_dx = screen_dx;
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

void Player::Render() {
	int x = this->x - this->GetCameraX();
	if (this->x > this->max_moving_x)
		x += this->x - this->max_moving_x;
	//std::cout << "rendering " << this->y << ","<< this->x << std::endl;
	al_draw_filled_rectangle(x, this->y, x + 16, this->y + 16, al_map_rgb(255, 32, 65));
}

int Player::GetCameraX(){
	if (this->x < this->camera_dx)
		return 0;
	else
		return this->x - this->camera_dx;
	
}