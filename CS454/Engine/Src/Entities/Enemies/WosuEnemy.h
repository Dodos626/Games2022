#pragma once
#ifndef WOSU_INCLUDE
#define WOSU_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"


class WosuEnemy : public Enemy {
public:
	WosuEnemy(Point* spawn);
	void AI();
};




#endif
