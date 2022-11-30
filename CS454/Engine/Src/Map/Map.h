#pragma once
#ifndef MAP_INCLUDE
#define MAP_INCLUDE
#include "../BitMap/BitMap.h"
#include "../Tiles/Map/TileMap.h"
#include <string>

class Map {
private:
	BitMap *bitmap;
	TileMap *tilemap;
public:
	Map(std::string tilemapPath, int tilemapWidth, int tilemapHeight, const char* bitmapPath, int tilesetWidth, int tilesetHeight);	void BlitSelf(int x, int y);
	void BlitBitMap(int x, int y);
	//void BlitBitMap(int starting_x, int starting_y);

};

#endif