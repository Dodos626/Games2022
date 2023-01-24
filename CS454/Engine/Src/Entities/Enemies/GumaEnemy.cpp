#include "GumaEnemy.h"

GumaEnemy::GumaEnemy(Point *spawn) : Enemy(spawn, "Engine/Configs/enemy/GumaConfig.json", "Engine/Configs/enemy/GumaAnimatorConfig.json") {
	this->name = "Guma";
}

void GumaEnemy::AI() {

}