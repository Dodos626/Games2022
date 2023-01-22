#pragma once
#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE


#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Utils/Point.h"
#include "../Animators/PlayerAnimator/PlayerAnimator.h"
#include "../Utils/player_state.h"



#define FIND_STATE(x, y) static_cast<p_state>(static_cast<int>(x)+ static_cast<int>(y)%2)


class Player {
private :
	int x, y;
	int camera_dx;
	int health;			//health points
	int lifes;
	int mana;
	int points;
 	int attack_power;	//attack damage
	int armor;			//armor is x where x is the damage it will prevent before health is affected
	bool duck;
	int height;


	//physics
	int speed;
	int max_moving_x;
	int fall_speed;
	int jump_speed;
	int jump_height;
	
	
	p_state state = p_state::idle_right;
	PlayerAnimator* animator; //players animator
public:
	Player(Point *spawn, int screen_width, int map_width, int screen_dx);
	
	//GETTERS
	int GetX(void) const { return x; }
	int GetCameraX(void);
	int GetY(void) const { return y; }
	int GetHealth(void) const { return health; }
	int GetAttackPower(void) const { return attack_power; }
	int GetArmor(void) const { return armor; }
	int GetSpeed(void) const { return speed; }
	int GetHeight(void) const { return height; }
	int GetPoints(void) const { return points; }
	int GetLifes(void) const { return lifes; }
	int GetMana(void) const { return mana; }
	int GetFallSpeed(void) const { return fall_speed; }
	int GetJumpSpeed(void) const { return jump_speed; }
	int GetJumpHeight(void) const { return jump_height; }
	p_state GetState(void) const { return state; }

	//SETTERS
	void setState(p_state state_) { this->state = state_; };
	void setStateWithDirection(p_state state_) { this->state = FIND_STATE(state_, this->state); }

	//Move
	void MoveLeft();
	void MoveRight(); //oso kounieme deksia kanw progress to move_right ama stamatisw na kounieme reset all animation
	void MoveUp();
	void MoveDown();
	void Stand();
	void Duck();
	void ChangeStance();
	void Respawn(Point *p);
	void StopMoving();
	bool isDucking(void) { return this->duck; };
	//Attack - Damage functions
	void TakeDamage(int damage);

	//Render
	void Render(double curr_time);
	
	
};

#endif
