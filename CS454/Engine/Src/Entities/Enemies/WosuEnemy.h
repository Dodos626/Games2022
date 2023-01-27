#pragma once
#ifndef WOSU_INCLUDE
#define WOSU_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"

enum class wosu_state {
	move_left,
	move_right
};

class WosuEnemy : public Enemy {
private:
	wosu_state state = wosu_state::move_left;
	int GetStateToInt(wosu_state state);
	
public:
	WosuEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_);
	void AI(Point player_position);
	void Render(double curr_time, int relative_x)override;
	void ChangeDirection() override;
};




#endif
