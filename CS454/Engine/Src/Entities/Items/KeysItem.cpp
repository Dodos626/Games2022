#include "KeyItem.h"

KeyItem::KeyItem(Point* spawn) : Item(spawn) {
	this->name = "Key";
	this->keys_increase = 1;

	std::vector<std::string> animations = { "key_animation" };
	this->animator = new PlayerAnimator("Engine/Configs/item/KeyAnimatorConfig.json",0, animations);

}
void KeyItem::PickUp(Player& player) {
	player.IncreaseKeys(this->keys_increase);
}
void KeyItem::Render(double curr_time) {
	this->animator->render(this->coordinates->GetX(), this->coordinates->GetY(), curr_time, 0);
}