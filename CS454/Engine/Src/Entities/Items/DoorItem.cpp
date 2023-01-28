#include "DoorItem.h"

DoorItem::DoorItem(Point* spawn) : Item(spawn) {
	this->name = "Door";
	this->width = 16;
	this->height = 32;
	this->is_locked = true;
	std::vector<std::string> animations = { "door" };
	this->animator = new PlayerAnimator("Engine/Configs/item/DoorAnimatorConfig.json", 0, animations);

}
void DoorItem::PickUp(Player& player) {
	if (player.UseKey())
		this->Unlock();
}

void DoorItem::Unlock() {
	this->is_locked = false;
	// Unlock animation here
}

void DoorItem::Render(double curr_time, int relative_x) {
	int x = this->coordinates->GetX() - relative_x;
	int y = this->coordinates->GetY();
	this->animator->render(x, y, curr_time, 0);
	//al_draw_rectangle(x, y, x + this->width, y + this->height, al_map_rgb(150, 0, 0), 0);
}