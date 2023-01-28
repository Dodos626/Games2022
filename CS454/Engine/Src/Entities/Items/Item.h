#pragma once
#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE
#include "../Entity.h"
#include <nlohmann/json.hpp>


class Item : public Entity {
	//just exists and is being rendered before enemies and player
	//if it collides with a player it's picked up
public:
	Item(Point* spawn);
	//~Item();
	void Collide(Player& player) { this->PickUp(player); };
	void GetAttacked(int damage, Point point_of_attack) {};
	std::string GetName() { return this->name; }
	virtual void PickUp(Player &player) = 0;
	virtual void Render(double curr_time, int relative_x);
};

#endif