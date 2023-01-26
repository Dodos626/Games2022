#include "Item.h"


Item::Item(Point* spawn) {
	this->coordinates = spawn;
	this->animator = NULL;
	this->width = 16;
	this->height = 16;
	//this->animator = new PlayerAnimator(animationpath, static_cast<int>(this->state), animation_names);
}

void Item::Render(double curr_time, int relative_x) {
	int x = this->coordinates->GetX();
	int y = this->coordinates->GetY();
	al_draw_filled_rectangle(x - relative_x, y, x + this->width, y + this->height, al_map_rgb(32, 255, 65));
}