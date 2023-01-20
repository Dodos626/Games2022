#include "Point.h"

Point *Point::operator+(Point *p2) {
	return new Point(this->x + p2->x, this->y + p2->y);
}