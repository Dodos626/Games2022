#include "MapEntities.h"

Enemy* MapEntities::GetEnemyFromString(std::string enemy_name, Point* spawn) {
	if (enemy_name == "Guma")
		return new GumaEnemy(spawn);
	else if (enemy_name == "PalaceBot")
		return new PalaceBotEnemy(spawn);
	else if (enemy_name == "Wosu")
		return new WosuEnemy(spawn);
	assert(0);
}

Item* MapEntities::GetItemFromString(std::string item_name, Point* spawn) {
	return NULL;
}