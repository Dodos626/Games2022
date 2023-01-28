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
#include "Spells/Spell.h"
#include "DisplayStats/DisplayStats.h"

#define FIND_STATE(x, y) static_cast<p_state>(static_cast<int>(x)+ static_cast<int>(y)%2)

class DisplayStats;
class Entity;

class Player {
private :
	int x, y;
	int camera_dx;
	int health , max_health;			//health points
	int lives;
	int mana , max_mana;
	int points;
 	int attack_power;	//attack damage
	bool duck;
	int height;
	int width;
	int damage_reduction;
	int keys;

	DisplayStats *stats_display;

	//physics
	int speed;
	int max_moving_x;
	int fall_speed;
	int jump_speed;
	int jump_height;
	bool is_attacking = false;
	// in case of a cancelled attack this offset applies to fix the right frame
	// because the animation will be shorter so  cancelled_attack_offset = Frames to render - Total frames
	int cancelled_attack_offset = 0; 
	
	//spells
	Spell_Book spell_book;
	
	p_state state = p_state::idle_right;
	PlayerAnimator* animator; //players animator

	//immunity
	bool is_damaged = false;
	double immunity = 0;
	Point point_of_attack;

	void CreateSpellBook(void);
	
	//spell shield
	void spellShield(void);
	void counterSpellShield(void);
	
	//spell jump
	void spellJump(void);
	void counterSpellJump(void);
	
	//spell life
	void spellLife(void);

	//spell fairy
	void spellFairy(void);
	void counterSpellFairy(void);


	//toggles
	bool toggle_collision_box = false;
	
public:
	Player(Point *spawn, int screen_width, int map_width, int screen_dx);
	
	~Player() {
		delete animator;
		delete stats_display;
	};
	
	//GETTERS
	int GetX(void) const { return x; }
	int GetCameraX(void);
	int GetY(void) const { return y; }
	int GetHealth(void) const { return health; }
	int GetAttackPower(void) const { return attack_power; }
	int GetSpeed(void) const { return speed; }
	int GetHeight(void) const { return height; }
	int GetWidth(void) const { return this->width; }
	int GetPoints(void) const { return points; }
	int GetLifes(void) const { return this->lives; }
	int GetMana(void) const { return mana; }
	int GetFallSpeed(void) const { return fall_speed; }
	int GetJumpSpeed(void) const { return jump_speed; }
	int GetJumpHeight(void) const { return jump_height; }
	p_state GetState(void) const { return state; }
	bool isDucking(void) { return this->duck; };

	//SETTERS
	void setState(p_state state_) { 
		if (this->is_attacking || this->is_damaged) return;
		this->state = state_; 
	};
	void setStateWithDirection(p_state state_) { 
		if (this->is_attacking || this->is_damaged) return;
		this->state = FIND_STATE(state_, this->state); 
	}
	void LoadStats(int map_width,  int map_height, int y_offset);

	//Move
	void AnimateMoveRight();
	void AnimateMoveLeft();

	

	void ChangeStance();
	void Duck();
	void MoveLeft();
	void MoveRight(); //oso kounieme deksia kanw progress to move_right ama stamatisw na kounieme reset all animation
	void MoveUp();
	void MoveDown();

	void Stand();
	void Respawn(Point *p);
	void StopMoving();

	//Attacks
	void Attack();
	void CancelledAttack();
	Point GetAttackPoint();

	// Actions
	void TakeDamage(int damage, Point point_of_attack);
	void RegenerateHealth(int hp_gain);
	void RegenerateMana(int mana_gain);
	void IncreaseLives(int difference);
	void IncreasePoints(int points);
	void IncreaseKeys(int keys);

	//Render
	void Render(double curr_time);
	void RenderAttack(double curr_time);

	//Spells
	void castSpell(int id) {
		this->mana -= this->spell_book.cast(id, this->mana);
	}

	void RegisterSpell(std::function<void(void)> f, int cost) {
		this->spell_book.registerSpell(new Spell(cost,f,nullptr,true));
	}

	/*
	* checks all active spells if their effect is over
	* the it calls the counter spell if it exists
	* to remove the effect
	*/
	void CheckSpellTimer(double curr_time) {
		this->spell_book.checkIfSpellsEnded(curr_time);
	}

	void ToggleCollisionBoxRender() {
		this->toggle_collision_box = !this->toggle_collision_box;
	}

	void LoadStats();
	friend class DisplayStats;
	friend class Entity;
};

#endif
