#include "ManaPotionItem.h"

ManaPotionItem::ManaPotionItem(Point* spawn) : Item(spawn, "Engine/Configs/item/HealthPotionAnimator.json") {
	this->name = "ManaPotion";
	this->mana_gain = 20;

}
void ManaPotionItem::PickUp(Player& player) {
	player.RegenerateMana(this->mana_gain);
}
