#include "Map.h"

Map::Map(std::string tilemapPath, int tilemapWidth , int tilemapHeight, const char* bitmapPath, int tilesetWidth, int tilesetHeight) {
	this->bitmap = new BitMap(bitmapPath, tilesetWidth, tilesetHeight);
	this->tilemap = new TileMap(tilemapWidth, tilemapHeight, tilemapPath);
}

void Map::BlitSelf(int x, int y) {
	int tile = 0;
	int max_height = this->tilemap->getTilemapHeight();
	int max_width = this->tilemap->getTilemapWidth();

	for (int height = 0; height < max_height; height++) {
		for (int width = 0 ; width < max_width; width++) {
			tile = this->tilemap->getTile(width, height);
			this->bitmap->BlitTile(tile, x + width * 16, y + height * 16);
		}
	}
	
	
}

void Map::BlitBitMap(int x, int y) {
	al_draw_bitmap(this->bitmap->getBitMap(), x, y, 0);
}

