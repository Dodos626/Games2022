#pragma once
#ifndef PALACEBOT_INCLUDE
#define PALACEBOT_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"

enum class palaceBot_state {
	red,
	blue,
	cyan
};

class PalaceBotEnemy : public Enemy {
private:
	palaceBot_state state = palaceBot_state::red;
public:
	PalaceBotEnemy(Point* spawn);
	void AI();
	int GetStateToInt(palaceBot_state state);
	void Render(double curr_time, int relative_x)override;
};




#endif
