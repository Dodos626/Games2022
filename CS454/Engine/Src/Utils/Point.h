#pragma once
#ifndef POINT_INCLUDE
#define POINT_INCLUDE
#include <iostream>

class Point {
protected:
	int x, y;
public:
	Point(void) { this->x = -1; this->y = -1; };
	Point(int x, int y);
	
	int GetX() const { return this->x; }
	int GetY() const { return this->y; }
	
	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }

	void AddToX(int dx) { this->x += dx; }
	void AddToY(int dy) { this->y += dy; }

	bool InRectangle(Point &p, int dx, int dy);

	bool operator==(const Point &p2) { return this->x == p2.x && this->y == p2.y; };
	Point &operator+(Point &p2);
	int operator-(Point* p2);
	friend std::ostream &operator<<(std::ostream& os, const Point &p);
};

#endif