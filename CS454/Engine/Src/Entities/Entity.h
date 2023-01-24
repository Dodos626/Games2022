#pragma once
#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE
#include "../Utils/Point.h"
#include "../Animators/Animator.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

class Entity {
protected:
	Point *coordinates; // where it is
	int height, width; // size
	Animator* animator;
	std::string name;
public:
	//Getters
	Point *GetCoordinates() { return this->coordinates; }
	int GetHeight() { return this->height; }
	int GetWidth() { return this->width; }

	void Render();
	bool Collides(Point* p) { return *p == *this->coordinates; }
	
	friend std::ostream& operator<<(std::ostream& os, const Entity& p);

};

#endif