#pragma once
#ifndef GUMA_INCLUDE
#define GUMA_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"


class GumaEnemy : public Enemy {
public:
	GumaEnemy(Point *spawn);
	void AI();
};




#endif
