#pragma once
#ifndef HEALTHPOT_INCLUDE
#define HEALTHPOT_INCLUDE
#include "Item.h"


class HealthPotionItem : public Item {
	//on pickup heals the player and then disappears
private:
	int health_gain;
public:
	HealthPotionItem(Point* spawn);
	void PickUp(Player& player);
};

#endif
