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
	bool moves_right = false;
	palaceBot_state state = palaceBot_state::red;
public:
	PalaceBotEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_);
	void AI(Player& player);
	int GetStateToInt(palaceBot_state state);
	void Render(double curr_time, int relative_x)override;
	void GetAttacked(int damage, Point point_of_attack)override;
	void ChangeDirection() {
		if (this->immunity > 0) { return; }
		this->immunity = 0.5;
		this->moves_right = !this->moves_right;
	}
	void SuffleAnimation();
};




#endif
