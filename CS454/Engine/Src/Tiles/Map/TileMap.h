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
	std::vector<int> getMap() { return this->map; }
	int getTilemapWidth() { return this->width; }
	int getTilemapHeight() { return this->height; }
	int getTile(int x, int y) { return this->map[y * this->width + x]; }
	
	
};



#endif