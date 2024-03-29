#pragma once
#ifndef MAPENTITIES_INCLUDE
#define MAPENTITIES_INCLUDE
#include <assert.h>
#include "../Entities/Enemies/Enemy.h"
#include "../Entities/Enemies/GumaEnemy.h"
#include "../Entities/Enemies/PalaceBotEnemy.h"
#include "../Entities/Enemies/WosuEnemy.h"
#include "../Entities/Enemies/StaflosEnemy.h"

#include "../Entities/Items/Item.h"
#include "../Entities/Items/HealthPotionItem.h"
#include "../Entities/Items/ManaPotionItem.h"
#include "../Entities/Items/LifeUpItem.h"
#include "../Entities/Items/KeyItem.h"
#include "../Entities/Items/PointBagItem.h"
#include "../Entities/Items/Sword.h"
#include "../Entities/Items/DoorItem.h"

#include "../Entities/Objects/Elevator.h"
#include "Point.h"


namespace MapEntities {
	using Action = std::function<bool(int, int, int, int)>;
	Enemy* GetEnemyFromString(std::string enemy_name, Point* spawn, Action tryMoveLeft, Action tryMoveRight, Action tryMoveUp, Action tryMoveDown);
	Item* GetItemFromString(std::string item_name, Point* spawn);
	ElevatorStatus GetElevatorStatusFromString(std::string status);
}


#endif