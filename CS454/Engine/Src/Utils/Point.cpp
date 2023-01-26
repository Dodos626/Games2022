#include "Point.h"

Point *Point::operator+(Point *p2) {
	return new Point(this->x + p2->x, this->y + p2->y);
}

int Point::operator-(Point* p2) {
	return ((this->x - p2->x) * (this->x - p2->x) + (this->y - p2->y) * (this->y - p2->y));
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}


std::ostream &operator<<(std::ostream &os, const Point &p) {
	std::cout << p.x << ", " << p.y;
	return std::cout;
}