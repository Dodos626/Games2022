#include "Screen.h"

Screen::Screen(int width, int height) {
	this->width = width;
	this->height = height;
	this->display = al_create_display(width, height);
}

void Screen::SetScalingFactor(int tilesize) {

	/**
	int scaling = 1;
	int w = this->width;
	int h = this->height;
	int tilePixels = tilesize * tilesize;
	
	//for small screens
	if (w <= 800 && h <= 600) {
		this->scalingFactor = 1;
		return;
	}


	//working prototype
	while ((w*h)/(tilePixels * scaling) > 1600) { 
		
		scaling++;
	}
	
	
	this->scalingFactor = scaling % 2 ? scaling + 1 : scaling ;
	
	
	std::cout << "Scaling factor: " << this->scalingFactor << std::endl;
	*/
	this->scalingFactor = 2;
}