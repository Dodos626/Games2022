#pragma once
#ifndef POINT_INCLUDE
#define POINT_INCLUDE
#include <iostream>

class Point {
private:
	int x, y;
	std::string info;
public:
	Point(int x, int y);
	Point(int x, int y, std::string info);
	
	int GetX() { return this->x; };
	int GetY() { return this->y; };
	std::string GetInfo() { return this->info; };
	
	void SetX(int x) { this->x = x; };
	void SetY(int y) { this->y = y; };

	bool operator==(const Point &p2) { return this->x == p2.x && this->y == p2.y; };
	Point *operator+(Point* p2);
	friend std::ostream &operator<<(std::ostream& os, const Point &p);
};

#endif