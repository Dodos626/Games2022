#include "PalaceBotEnemy.h"

PalaceBotEnemy::PalaceBotEnemy(Point* spawn) : Enemy(spawn, "Engine/Configs/enemy/PalaceBotConfig.json", "Engine/Configs/enemy/PalaceBotAnimatorConfig.json") {
	this->name = "PalaceBot";
}

void PalaceBotEnemy::AI() {

}