#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}


Point &Point::operator+(Point &p2) {
	Point new_point(this->x + p2.x, this->y + p2.y);
	return new_point;
}

int Point::operator-(Point* p2) {
	return ((this->x - p2->x) * (this->x - p2->x) + (this->y - p2->y) * (this->y - p2->y));
}


bool Point::InRectangle(Point &p, int dx, int dy) {
	return this->x <= p.x && p.x <= this->x + dx && this->y <= p.y && p.y <= this->y + dy;
}


std::ostream &operator<<(std::ostream &os, const Point &p) {
	os << p.x << ", " << p.y;
	return os;
}