#pragma once
#ifndef GUMA_INCLUDE
#define GUMA_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"
#include <vector>
enum class guma_state {
	move_left,
	move_right,
	hurl_left,
	hurl_right,
	atack_left,
	atack_right
};
static const std::vector<std::string> animation_names = { "guma_move_left", "guma_move_right", "guma_hurls_left", "guma_hurls_right", "guma_proj_left", "guma_proj_right" };
class GumaEnemy : public Enemy {
private:
	guma_state state = guma_state::move_left;
public:
	void Render(double curr_time, int relative_x) override;
	int GetStateToInt(guma_state state);
	GumaEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_);
	void AI(Point player_position);
	void ChangeDirection()
	{
		;
	};
};




#endif
