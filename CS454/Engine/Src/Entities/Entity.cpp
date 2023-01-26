#include "Entity.h"


void Entity::Render(double curr_time, int relative_x) {
	int x = this->coordinates->GetX();
	int y = this->coordinates->GetY();

	al_draw_filled_rectangle(x, y, x + this->width, y + this->height, al_map_rgb(255, 32, 65));
}

void Entity::MoveLeft() {
	//if (this->duck || this->is_attacking)
	//	return;
	this->coordinates->AddToX(-1);
}

void Entity::MoveRight() {
	//if (this->duck || this->is_attacking) {
	//	return;
	//}
	this->coordinates->AddToX(1);
}

void Entity::MoveUp() {
	//this->Stand();
	//setStateWithDirection(p_state::jump_left);
	this->coordinates->AddToY(-1);
}

void Entity::MoveDown() {
	//this->setStateWithDirection(p_state::land_left);
	this->coordinates->AddToY(1);
}

std::ostream& operator<<(std::ostream& os, const Entity& p) {
	std::cout << p.name << std::endl;
	return std::cout;
}