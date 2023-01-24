#include "KeyItem.h"

KeyItem::KeyItem(Point* spawn) : Item(spawn, "Engine/Configs/item/HealthPotionAnimator.json") {
	this->name = "LifeUp";
	this->keys_increase = 1;

}
void KeyItem::PickUp(Player& player) {
	player.IncreaseKeys(this->keys_increase);
}
