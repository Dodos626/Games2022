#pragma once
#ifndef PROJECTILE_INCLUDE
#define PROJECTILE_INCLUDE

#include "../Animators/PlayerAnimator/PlayerAnimator.h"
#include "../Utils/Point.h"
#include "../Player/Player.h"
#include <vector>
#include <assert.h>

enum class ProjectileDirection {
	fly_left = 0,
	fly_right
};

class Projectile {
private:
	using Action = std::function<bool(int, int, int, int)>; // to bind the tryMoveX functions
	Action tryMoveLeft, tryMoveRight;
	ProjectileDirection direction;
	PlayerAnimator* animator;
	Point* location;
	int speed;
	int range;
	int width;
	int height;
	int damage;
	int GetStateToInt(ProjectileDirection direction);
	bool is_flying;
public:
	
	Projectile(Point* spawn, ProjectileDirection direction, Action tryMoveLeft_, Action tryMoveRight_);
	void AI(Player &player);
	int GetX() { return this->location->GetX(); }
	int GetY() { return this->location->GetY(); }
	bool isFlying() { return this->is_flying; }
	void MoveRight() { this->location->AddToX(1); }
	void MoveLeft() { this->location->AddToX(-1); }
	int GetDamage() { return this->damage; }
	void Stop() { this->is_flying = false; }
	void Render(double curr_time, int relative_x);
	
	~Projectile() {
		delete this->location;
		delete this->animator;
	}
};




#endif
