#pragma once
#ifndef TileMapInclude
#define TileMapInclude
#include <vector>
#include <string>
#include "../Parser/TileParser.h"
#include <assert.h>


class TileMap {
private:
	std::vector<std::vector<int>> map;
	int width;
	int height;
	int setMap(std::string path);
public:
	TileMap(int width, int height, std::string path);
	void PrintSelf();
	std::vector<std::vector<int>> getMap() { return this->map; }
	int getTilemapWidth() { return this->width; }
	int getTilemapHeight() { return this->height; }
	int getTile(int x, int y) { assert(x >= 0 && x < this->width&& y >= 0 && y < this->height); return this->map[y][x]; }
	
	
};



#endif