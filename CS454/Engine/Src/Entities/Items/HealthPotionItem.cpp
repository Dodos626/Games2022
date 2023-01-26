#include "HealthPotionItem.h"

HealthPotionItem::HealthPotionItem(Point* spawn) : Item(spawn) {
	std::vector<std::string> animation_names = { "HealthPotion" };
	this->animator = new PlayerAnimator("Engine/Configs/item/HealthPotionAnimatorConfig.json", 0, animation_names);
	this->name = "HealthPotion";
	this->health_gain = 20;

}
void HealthPotionItem::PickUp(Player& player) {
	player.RegenerateHealth(this->health_gain);
}


void HealthPotionItem::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 0);
}