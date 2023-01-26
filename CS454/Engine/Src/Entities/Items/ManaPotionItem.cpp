#include "ManaPotionItem.h"

ManaPotionItem::ManaPotionItem(Point* spawn) : Item(spawn) {
	this->name = "ManaPotion";
	this->mana_gain = 20;

	this->animator = new PlayerAnimator("Engine/Configs/item/ManaPotionAnimatorConfig.json", 0, { "mana_potion_animation" });
}
void ManaPotionItem::PickUp(Player& player) {
	player.RegenerateMana(this->mana_gain);
}

void ManaPotionItem::Render(double curr_time) {
	this->animator->render(this->coordinates->GetX(), this->coordinates->GetY(), curr_time, 0);
}