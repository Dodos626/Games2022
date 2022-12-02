#pragma once
#ifndef SCREENINCLUDE
#define SCREENINCLUDE
#include <iostream>
#include <allegro5/allegro5.h>

class Screen {
private:
	int width, height;
	int scalingFactor = 1;
	ALLEGRO_DISPLAY* display;
public:
	Screen(int width, int height);
	int GetWidth(void) const { return width; }
	int GetHeight(void) const { return height; }
	void SetScalingFactor(int tilesize);
	int GetScalingFactor() { return this->scalingFactor; }
	ALLEGRO_DISPLAY* GetDisplay(void) { return display; }
	
};
#endif