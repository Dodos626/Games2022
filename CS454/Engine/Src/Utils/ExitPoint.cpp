#include "ExitPoint.h"

ExitPoint::ExitPoint(int x, int y, std::string next_map_name, Point *next_spawn) : Point(x,y) {
	this->next_map_name = next_map_name;
	this->next_spawn = next_spawn;
}