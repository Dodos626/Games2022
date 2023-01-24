#pragma once
#ifndef PALACEBOT_INCLUDE
#define PALACEBOT_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"


class PalaceBotEnemy : public Enemy {
public:
	PalaceBotEnemy(Point* spawn);
	void AI();
};




#endif
