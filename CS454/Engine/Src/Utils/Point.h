#pragma once
#ifndef POINT_INCLUDE
#define POINT_INCLUDE
class Point {
private:
	int x, y;
public:
	Point(int x, int y);
	
	int GetX() { return this->x; };
	int GetY() { return this->y; };
	
	void SetX(int x) { this->x = x; };
	void SetY(int y) { this->y = y; };

	bool operator==(Point *p2) { return this->x == p2->x && this->y == p2->y; };
	Point *operator+(Point* p2);
};

#endif