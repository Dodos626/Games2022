#pragma once
#ifndef MAPENTITIES_INCLUDE
#define MAPENTITIES_INCLUDE
#include <assert.h>
#include "../Entities/Enemies/Enemy.h"
#include "../Entities/Enemies/GumaEnemy.h"
#include "../Entities/Enemies/PalaceBotEnemy.h"
#include "../Entities/Enemies/WosuEnemy.h"

#include "../Entities/Items/Item.h"

#include "Point.h"


namespace MapEntities {
	Enemy* GetEnemyFromString(std::string enemy_name, Point* spawn);
	Item* GetItemFromString(std::string item_name, Point* spawn);
}


#endif