#include "PointBagItem.h"

PointBagItem::PointBagItem(Point* spawn, bool is_big) : Item(spawn) {
	if (is_big) {
		this->name = "BigPointBag";
		this->points_increase = 500;
	}
	else {
		this->name = "PointBag";
		this->points_increase = 50;
	}

	this->animator = new PlayerAnimator("Engine/Configs/item/PointBagAnimatorConfig.json", 0, { "point_bag_animation" });

}


void PointBagItem::PickUp(Player& player) {
	player.IncreasePoints(this->points_increase);
}

void PointBagItem::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX()-relative_x, this->coordinates->GetY(), curr_time, 0);
}