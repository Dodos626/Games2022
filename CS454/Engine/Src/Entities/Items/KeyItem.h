#pragma once
#ifndef KEY_INCLUDE
#define KEY_INCLUDE
#include "Item.h"


class KeyItem : public Item {
private:
	int keys_increase;
public:
	KeyItem(Point* spawn);
	void PickUp(Player& player);
};

#endif
