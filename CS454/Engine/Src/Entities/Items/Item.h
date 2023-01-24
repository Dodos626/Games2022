#pragma once
#ifndef ITEM_INCLUDE
#define ITEM_INCLUDE
#include "../Entity.h"

class Item : public Entity {
	//just exists and is being rendered before enemies and player
	//if it collides with a player it's picked up
public:
	
};

class HealthPotion : Item {
	//on pickup heals the player and then disappears
};



#endif