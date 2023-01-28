#include "MapEntities.h"

Enemy* MapEntities::GetEnemyFromString(std::string enemy_name, Point* spawn, Action tryMoveLeft, Action tryMoveRight, Action tryMoveUp, Action tryMoveDown) {
	if (enemy_name == "Guma")
		return new GumaEnemy(spawn, tryMoveLeft, tryMoveRight, tryMoveUp, tryMoveDown);
	else if (enemy_name == "PalaceBot")
		return new PalaceBotEnemy(spawn, tryMoveLeft, tryMoveRight, tryMoveUp, tryMoveDown);
	else if (enemy_name == "Wosu")
		return new WosuEnemy(spawn, tryMoveLeft, tryMoveRight, tryMoveUp, tryMoveDown);
	else if (enemy_name == "Staflos")
		return new StaflosEnemy(spawn, tryMoveLeft, tryMoveRight, tryMoveUp, tryMoveDown);
	assert(0);
	return NULL;
}

Item* MapEntities::GetItemFromString(std::string item_name, Point* spawn) {
	if (item_name == "HealthPotion")
		return new HealthPotionItem(spawn);
	else if (item_name == "ManaPotion")
		return new ManaPotionItem(spawn);
	else if (item_name == "LifeUp")
		return new LifeUpItem(spawn);
	else if (item_name == "Key")
		return new KeyItem(spawn);
	else if (item_name == "PointBag")
		return new PointBagItem(spawn, false);
	else if (item_name == "BigPointBag")
		return new PointBagItem(spawn, true);
	else if (item_name == "Sword")
		return new SwordItem(spawn);
	assert(0);
	return NULL;
}

ElevatorStatus MapEntities::GetElevatorStatusFromString(std::string status) {
	if (status == "moving_up")
		return ElevatorStatus::moving_up;
	else if (status == "moving_down")
		return ElevatorStatus::moving_down;
	else if (status == "is_up")
		return ElevatorStatus::is_up;
	else if (status == "is_down")
		return ElevatorStatus::is_down;
	else
		assert(0);

}