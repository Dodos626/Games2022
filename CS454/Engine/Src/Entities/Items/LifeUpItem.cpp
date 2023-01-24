#include "LifeUpItem.h"

LifeUpItem::LifeUpItem(Point* spawn) : Item(spawn, "Engine/Configs/item/HealthPotionAnimator.json") {
	this->name = "LifeUp";
	this->lives_increase = 1;

}
void LifeUpItem::PickUp(Player& player) {
	player.IncreaseLives(this->lives_increase);
}
