#pragma once
#ifndef MANAPOT_INCLUDE
#define MANAPOT_INCLUDE
#include "Item.h"


class ManaPotionItem : public Item {
private:
	int mana_gain;
public:
	ManaPotionItem(Point* spawn);
	void PickUp(Player& player);
	void Render(double curr_time);
};

#endif
