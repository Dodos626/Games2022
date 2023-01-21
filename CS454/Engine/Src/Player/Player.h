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






class Player {
private :
	int x, y;
	int camera_dx;
	int health;			//health points
 	int attack_power;	//attack damage
	int armor;			//armor is x where x is the damage it will prevent before health is affected
	int speed;
	int max_moving_x;
	bool duck;
	int height;
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
	p_state GetState(void) const { return state; }

	//SETTERS
	void setState(p_state state_) { this->state = state_; };

	//Move
	void MoveLeft();
	void MoveRight(); //oso kounieme deksia kanw progress to move_right ama stamatisw na kounieme reset all animation
	void MoveUp();
	void MoveDown() { this->y += this->speed; }
	void Stand();
	void Duck();
	void ChangeStance();
	void Respawn(Point *p);
	bool isDucking(void) { return this->duck; };
	//Attack - Damage functions
	void TakeDamage(int damage);

	//Render
	void Render(double curr_time);
	
	
};

#endif
