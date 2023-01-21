#pragma once
#ifndef SCREENINCLUDE
#define SCREENINCLUDE
#include <iostream>
#include <allegro5/allegro5.h>

class Screen {
private:
	int width, height, scaledWidth, scaledHeight;
	int scalingFactor = 1;
	ALLEGRO_DISPLAY* display;
public:
	Screen(int width, int height, int scale);
	int GetWidth(void) const { return width; }
	int GetHeight(void) const { return height; }
	
	int GetScalingFactor() { return this->scalingFactor; }
	ALLEGRO_DISPLAY* GetDisplay(void) { return display; }
	
	int GetScaledWidth() const{ return scaledWidth; }
	int GetScaledHeight() const { return scaledHeight; }
	
};
#endif