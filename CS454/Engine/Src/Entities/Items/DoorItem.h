#pragma once
#ifndef DOOR_INCLUDE
#define DOOR_INCLUDE
#include "Item.h"


class DoorItem : public Item {
private:
	bool is_locked;
	void Unlock();
public:
	DoorItem(Point* spawn);
	void PickUp(Player& player);
	void Render(double curr_time, int relative_x) override;
	bool GetIsLocked() { return this->is_locked; }
};

#endif
