#pragma once
#ifndef MAP_INCLUDE
#define MAP_INCLUDE
#include "../BitMap/BitMap.h"
#include "../Tiles/Map/TileMap.h"
#include <string>
#include <vector>
#include <algorithm>

#define MUL_16(x) (x << 4)
class Map {
private:
	BitMap *bitmap;   //png
	TileMap *tilemap; //csv
	ALLEGRO_BITMAP *map_buffer; // whole map buffer
	std::vector<int> SolidBlockIds;
	std::vector<std::vector<bool>> grid;
	int player_dx;
public:
	Map(std::string tilemapPath, int tilemapWidth, int tilemapHeight, const char* bitmapPath, int bitmapWidth, int bitmapHeight , std::vector<int> SolidBlockIds);
	void PrecomputeMap();
	void Render(int left_x, int max_x, int y, int max_y);
	BitMap* getBitMap() { return this->bitmap; };
	TileMap* getTileMap() { return this->tilemap; };
	ALLEGRO_BITMAP* getMapBuffer() { return this->map_buffer; };
	bool IsSolid(int x, int y);

};

#endif