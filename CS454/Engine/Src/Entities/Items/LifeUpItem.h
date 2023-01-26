#pragma once
#ifndef LIFEUP_INCLUDE
#define LIFEUP_INCLUDE
#include "Item.h"


class LifeUpItem : public Item {
private:
	int lives_increase;
public:
	LifeUpItem(Point* spawn);
	void PickUp(Player& player);
	void Render(double curr_time, int relative_x)override;
};

#endif
