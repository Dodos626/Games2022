#pragma once
#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE
#include "../Utils/Point.h"

class Entity {
protected:
	Point coordinates; // where it is
	int height, width; // size
public:

	//Getters
	Point GetCoordinates() { return this->coordinates; }
	int GetHeight() { return this->height; }
	int GetWidth() { return this->width; }
	

	
	virtual void Render() = 0;
	virtual bool Collides(Point p) = 0;
	virtual void OnCollision() = 0; // if the player collides with it
	virtual void Move() = 0; // creatures move items don't
	virtual void Destroy() = 0; // in case of pickup / death
	
};

#endif