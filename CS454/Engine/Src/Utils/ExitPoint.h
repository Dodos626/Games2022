#pragma once
#ifndef EXITPOINT_INCLUDE
#define EXITPOINT_INCLUDE
#include "Point.h"


class ExitPoint : public Point {
private:
	std::string next_map_name;
	Point *next_spawn;
public:
	ExitPoint(int x, int y, std::string next_map_name, Point *next_spawn);

	Point *GetNextSpawn() const { return this->next_spawn; };
	std::string GetNextMapName() const { return this->next_map_name; };
};

#endif