#include "LifeUpItem.h"

LifeUpItem::LifeUpItem(Point* spawn) : Item(spawn) {
	this->name = "LifeUp";
	this->lives_increase = 1;

	std::vector<std::string> animations = { "life_up_animation" };
	this->animator = new PlayerAnimator("Engine/Configs/item/LifeUpAnimatorConfig.json", 0, animations);

}
void LifeUpItem::PickUp(Player& player) {
	player.IncreaseLives(this->lives_increase);
}

void LifeUpItem::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time,0);
}