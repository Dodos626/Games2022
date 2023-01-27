#pragma once
#ifndef SWORD_INCLUDE
#define SWORD_INCLUDE
#include "Item.h"

class SwordItem : public Item {
	//on pickup heals the player and then disappears
private:
public:
	SwordItem(Point* spawn);
	void PickUp(Player& player);
	void Render(double curr_time, int relative_x)override;
};


#endif
