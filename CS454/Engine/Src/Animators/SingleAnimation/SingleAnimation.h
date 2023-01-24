#pragma once
#ifndef SINGLE_ANIMATION_INCLUDE
#define SINGLE_ANIMATION_INCLUDE

#include <vector>
#include "./../../Utils/Point.h"
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;


class Mappings { // coordinates of each frame in the spread sheet
private:
	Point coordinates;
	int width, height;
public:
	Mappings(int x_, int y_, int width_, int height_) :
		coordinates(x_,y_), width(width_), height(height_) {};
	
	int getX() { return this->coordinates.GetX(); };
	int getY() { return this->coordinates.GetY(); };
	int getHeight() { return this->height; };
	int getWidth() { return this->width; };
};

//Holds one specific animation
// the number of frames , the time it takes for the animation
// and the mappings to the spritesheet
class SingleAnimation {
private:
	double total_time_passed = 0; // the last time we animated
	int number_of_frames;
	double frame_duration; // duration of frame
	int curr_selected_frame = 0;

	// mappings = x,y,width,height of every frame in this single animation
	std::vector<Mappings *> mappings;
	void progressAnimation(void);
	void registerMappings(json data);
public:
	SingleAnimation(json data);
	~SingleAnimation();
	int getNumberOfFrames(void) { return this->number_of_frames; };
	double getFrameDuration(void) { return this->frame_duration; };
	int getCurrSelectedFrame(void) { return this->curr_selected_frame; };
	Mappings *getMapping(double current_time);
	void resetAnimation(void){ this->curr_selected_frame = 0; };
};



#endif
