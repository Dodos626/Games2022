#include "HealthPotionItem.h"

HealthPotionItem::HealthPotionItem(Point* spawn) : Item(spawn, "Engine/Configs/item/HealthPotionAnimator.json") {
	this->name = "HealthPotion";
	this->health_gain = 20;

}
void HealthPotionItem::PickUp(Player& player) {
	player.RegenerateHealth(this->health_gain);
}
