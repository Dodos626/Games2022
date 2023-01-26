#pragma once
#ifndef ENEMY_INCLUDE
#define ENEMY_INCLUDE
#include "../Entity.h"
#include "../Items/Item.h"
#include "../../Utils/Point.h"
#include <time.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>

class Enemy : public Entity {
protected:
	int health;
	int damage;
	int points;
	int drop_chance;
	int percentage;
	std::vector<Item*> drops;
	bool is_alive;
	Item* dropped_item;
	//add state
	void _DropItem();
	void _Death();
	
public:
	Enemy(Point* spawn, std::string datapath);

	virtual void AI() = 0;
	void Collide(Player& player);

	int GetHP() const { return this->health; }
	int GetDamage() const { return this->damage; }
	int GetSpeed() const { return this->speed; }
	int GetPoints() const { return this->points; }
	bool GetIsAlive() const { return this->is_alive; }
	Item *GetDroppedItem() const { return this->dropped_item; }

	void GetDamaged(int damage);
	//has a animator
	//has a state
	//has a health
	//has a damage
	//has a speed
	//has points
	//has on death chance to drop an item
	//has an ai that takes players x,y and decides next move
};



#endif