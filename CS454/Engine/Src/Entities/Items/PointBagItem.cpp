#include "PointBagItem.h"

PointBagItem::PointBagItem(Point* spawn, bool is_big) : Item(spawn, "Engine/Configs/item/HealthPotionAnimator.json") {
	if (is_big) {
		this->name = "BigPointBag";
		this->points_increase = 500;
	}
	else {
		this->name = "PointBag";
		this->points_increase = 50;
	}

}


void PointBagItem::PickUp(Player& player) {
	player.IncreasePoints(this->points_increase);
}
