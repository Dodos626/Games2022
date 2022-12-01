#pragma once
#ifndef BITMAPINCLUDE
#define BITMAPINCLUDE

#include <stdio.h>
#include <iostream>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

class BitMap
{
private:
	ALLEGRO_BITMAP* BitMapPng;
	int tilesetWidth;
	int tilesetHeight;
public:
	BitMap(const char* path, int tilesetWidth, int tilesetHeight);
	ALLEGRO_BITMAP* getBitMap();
	void BitMapDestoy();
	ALLEGRO_BITMAP* getTile(int id);
	void BlitTile(int id, int x, int y); // TODO delete this
	int getTilesetWidth(){return this->tilesetWidth;}
	int getTilesetHeight(){return this->tilesetHeight;}
};

#endif