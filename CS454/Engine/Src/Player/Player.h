#pragma once
#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE


#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>






enum class p_direction {
	LEFT, RIGHT, UP, DOWN
};

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
public:
	Player(int x, int y, int screen_width, int map_width, int screen_dx);
	
	//GETTERS
	int GetX(void) const { return x; }
	int GetCameraX(void);
	int GetY(void) const { return y; }
	int GetHealth(void) const { return health; }
	int GetAttackPower(void) const { return attack_power; }
	int GetArmor(void) const { return armor; }
	int GetSpeed(void) const { return speed; }
	int GetHeight(void) const { return height; }

	//Move
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown() { this->y += this->speed; }
	void Stand();
	void Duck();
	void ChangeStance();
	void Respawn(int x, int y);
	//Attack - Damage functions
	void TakeDamage(int damage);

	//Render
	void Render();
	
	
};

#endif
