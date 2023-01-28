#pragma once
#ifndef GUMA_INCLUDE
#define GUMA_INCLUDE
#include "Enemy.h"
#include "../Items/Item.h"
#include "../../Animators/Animator.h"
#include "../../Utils/Point.h"
#include "../Projectile.h"
#include <vector>
enum class guma_state {
	move_left,
	move_right,
	atack_left,
	atack_right,
	idle_left,
	idle_right
};
static const std::vector<std::string> animation_names = { "guma_move_left", "guma_move_right", "guma_attack_left", "guma_attack_right" ,"guma_idle_left", "guma_idle_right"};
class GumaEnemy : public Enemy {
private:
	guma_state state = guma_state::move_left;
	bool is_attacking = false;
	double attack_cd = 0;
	std::vector<Projectile*> projectiles;
public:
	void Render(double curr_time, int relative_x) override;
	int GetStateToInt(guma_state state);
	GumaEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_);
	void AI(Player &player);
	
	void ChangeDirection()
	{
		;
	};

	void GetAttacked(int damage, Point point_of_attack)override;
	void ClearProjectiles();
	void SpawnProjectile(guma_state state);
	void AiProjectile(Player& player);
	void RenderProjectile(double curr_time, int relative_x);
};




#endif
