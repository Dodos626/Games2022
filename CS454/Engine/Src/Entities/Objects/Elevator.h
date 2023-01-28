#pragma once
#ifndef ELEVATOR_INCLUDE
#define ELEVATOR_INCLUDE
#include "../Entity.h"
#include "../Items/Item.h"
#include "../../Utils/Point.h"
#include <time.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <allegro5/allegro_primitives.h>


enum class ElevatorStatus {
	moving_up,
	moving_down,
	is_up,
	is_down
};

class Elevator : Entity {
private:
	ElevatorStatus status;
	bool isPlayerOn(Player& player);
	Point* stop_location;
public:
	Elevator(Point *location, Point *stop_location, ElevatorStatus status);
	Point* GetCoordinates() { return this->coordinates; }
	int GetHeight() { return this->height; }
	int GetWidth() { return this->width; }
	int GetX() const { return this->coordinates->GetX(); }
	int GetY() const { return this->coordinates->GetY(); }
	void GetAttacked(int damage, Point point_of_attack) { assert(0); }
	void Collide(Player& player) { assert(0); }
	bool HasToStop() { return this->coordinates->GetY() == this->stop_location->GetY(); }


	void MoveLeft() { ; };
	void MoveRight() { ; };

	void AI(Player& player); // all items take this implementation , enemies extend it

	void Render(double curr_time, int relative_x);
};

#endif
