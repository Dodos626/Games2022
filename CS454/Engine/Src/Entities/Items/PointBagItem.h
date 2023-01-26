#pragma once
#ifndef POINTBAG_INCLUDE
#define POINTBAG_INCLUDE
#include "Item.h"


class PointBagItem : public Item {
private:
	int points_increase;
public:
	PointBagItem(Point* spawn, bool is_big);
	void PickUp(Player& player);
	void Render(double curr_time)override;
};

#endif
