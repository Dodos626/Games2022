#pragma once
#ifndef STAFLOS_ENEMY_INCLUDE
#define STAFLOS_ENEMY_INCLUDE


#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"
#include <vector>
enum class staflos_state {
	move_left,
	move_right,
	atack_left,
	atack_right
};
class StaflosEnemy : public Enemy {
private:
	staflos_state state = staflos_state::move_left;
public:
	void Render(double curr_time) override;
	int GetStateToInt(staflos_state state);
	StaflosEnemy(Point* spawn);
	void AI();
};



#endif // !STAFLOS_ENEMY_INCLUDE
