#include "WosuEnemy.h"

WosuEnemy::WosuEnemy(Point* spawn) : Enemy(spawn, "Engine/Configs/enemy/WosuConfig.json", "Engine/Configs/enemy/WosuAnimatorConfig.json") {
	this->name = "Wosu";
}

void WosuEnemy::AI() {

}