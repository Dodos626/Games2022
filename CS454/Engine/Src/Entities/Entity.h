#pragma once
#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE
#include "../Utils/Point.h"
#include "../Animators/Animator.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "../Player/Player.h"

class Entity {
protected:
	Point *coordinates; // where it is
	int height, width; // size
	int speed;
	PlayerAnimator* animator;
	std::string name;
public:
	//Getters
	Point *GetCoordinates() { return this->coordinates; }
	int GetHeight() { return this->height; }
	int GetWidth() { return this->width; }
	int GetX() const { return this->coordinates->GetX(); }
	int GetY() const { return this->coordinates->GetY(); }

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();


	virtual void Render(double curr_time, int relative_x);
	bool CheckCollision(Point* p) { return *p == *this->coordinates; }
	virtual void Collide(Player &player) = 0;
		
	friend std::ostream& operator<<(std::ostream& os, const Entity& p);

};

#endif