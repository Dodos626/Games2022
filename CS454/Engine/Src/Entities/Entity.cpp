#include "Entity.h"


void Entity::Render(double curr_time) {
	int x = this->coordinates->GetX();
	int y = this->coordinates->GetY();

	al_draw_filled_rectangle(x, y, x + this->width, y + this->height, al_map_rgb(255, 32, 65));
}

std::ostream& operator<<(std::ostream& os, const Entity& p) {
	std::cout << p.name << std::endl;
	return std::cout;
}