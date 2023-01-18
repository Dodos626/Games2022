#include "Player.h"

using json = nlohmann::json;

Player::Player() {
	
	std::ifstream fin("Engine/Configs/PlayerConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	this->x = data["x"];
	this->y = data["y"];
	this->health = data["health"];
	this->attack_power = data["attack_power"];
	this->armor = data["armor"];
	this->speed = data["speed"];
	
	
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

void Player::Move(p_direction direction) {
	switch (direction)
	{
		case p_direction::LEFT:
			this->x -= this->speed;
			break;
		case p_direction::RIGHT:
			this->x += this->speed;
			break;
		case p_direction::UP:
			this->y -= this->speed;
			break;
		case p_direction::DOWN:
			this->y += this->speed;
			break;
	}
}

void Player::Render() {
	al_draw_filled_rectangle(0, this->y, 0 + 16, this->y + 16, al_map_rgb(255, 32, 65));
}