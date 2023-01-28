#include "BitMap.h"

BitMap::BitMap(const char* path, int tilesetWidth, int tilesetHeight)
{
	this->BitMapPng = al_load_bitmap(path);
	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP); // faster bitmaps
	if (!BitMapPng)
	{
		std::string error = path;
		throw("Error loading image with path : "+ error);
	}
	this->tilesetWidth = tilesetWidth;
	this->tilesetHeight = tilesetHeight;
	
}

ALLEGRO_BITMAP* BitMap::getBitMap()
{
	return this->BitMapPng;
}

void BitMap::BitMapDestoy()
{
	al_destroy_bitmap(this->BitMapPng);
}

ALLEGRO_BITMAP* BitMap::getTile(int id){
	int x = id % this->getTilesetWidth();
	int y = id / this->getTilesetWidth();
	ALLEGRO_BITMAP* tile = al_create_sub_bitmap(this->BitMapPng, x << 4, y << 4, 16, 16);
	return tile;
}

void BitMap::BlitTile(int id, int x, int y) {
	int tilesetWidth = this->getTilesetWidth();
	int pos_x = id % tilesetWidth;
	int pos_y = id / tilesetWidth;
	al_draw_bitmap_region(
		this->BitMapPng, 
		pos_x << 4, 
		pos_y << 4, 
		16, 
		16, 
		x, 
		y, 
		0);
}