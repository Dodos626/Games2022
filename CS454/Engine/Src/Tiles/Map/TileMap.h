#pragma once
#ifndef TileMapInclude
#define TileMapInclude
#include <vector>
#include <string>
#include "../Parser/TileParser.h"


class TileMap {
private:
	std::vector<int> map;
	int width;
	int height;
	int setMap(std::string path);
public:
	TileMap(int width, int height, std::string path);
	void PrintSelf();
	
};



#endif