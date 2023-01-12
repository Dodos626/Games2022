#pragma once
#ifndef MAP_INCLUDE
#define MAP_INCLUDE
#include "../BitMap/BitMap.h"
#include "../Tiles/Map/TileMap.h"
#include <string>
#include <vector>

#define MUL_16(x) (x << 4)
class Map {
private:
	BitMap *bitmap;   //png
	TileMap *tilemap; //csv
	ALLEGRO_BITMAP *map_buffer; // whole map buffer
public:
	Map(std::string tilemapPath, int tilemapWidth, int tilemapHeight, const char* bitmapPath, int bitmapWidth, int bitmapHeight);	
	void BlitSelf(int x, int y);
	void BlitSelf(int x, int y, int scaling_factor, int screen_width, int screen_height);
	void PrecomputeMap();
	void Render(int x, int max_x);
	BitMap* getBitMap() { return this->bitmap; };
	TileMap* getTileMap() { return this->tilemap; };
	ALLEGRO_BITMAP* getMapBuffer() { return this->map_buffer; };

};

#endif