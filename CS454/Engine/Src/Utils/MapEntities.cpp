#include "MapEntities.h"

Enemy* MapEntities::GetEnemyFromString(std::string enemy_name, Point* spawn) {
	if (enemy_name == "Guma")
		return new GumaEnemy(spawn);
	else if (enemy_name == "PalaceBot")
		return new PalaceBotEnemy(spawn);
	else if (enemy_name == "Wosu")
		return new WosuEnemy(spawn);
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
	assert(0);
	return NULL;
}