#include "Screen.h"

Screen::Screen(int width, int height, int scale) {
	this->width = width;
	this->height = height;
	this->scalingFactor = scale;
	this->scaledHeight = height / scale;
	this->scaledWidth = width / scale;
	this->display = al_create_display(width, height);
}

