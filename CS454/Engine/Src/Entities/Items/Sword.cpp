#include "Sword.h"


SwordItem::SwordItem(Point* spawn): Item(spawn) {
	std::vector<std::string> animation_names = { "sword_animation" };
	this->animator = new PlayerAnimator("Engine/Configs/item/SwordAnimatorConfig.json", 0, animation_names);
}
void SwordItem::PickUp(Player& player) {
	
}
void SwordItem::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 0);
}