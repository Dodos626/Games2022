#pragma once
#ifndef TIMERINCLUDE
#define TIMERINCLUDE
#include <allegro5/allegro5.h>
#include <iostream>
class Timer {
private:
	double old_time = 0;
	double new_time = 0;
	double delta = 0;
	double fps_timer = 0;
	double avg_fps = 0;
	ALLEGRO_TIMER* timer ;
	bool print_fps = false;
public:
	Timer(double fps_ticker);
	void fps();
	double getDelta() { return this->delta; }
	ALLEGRO_TIMER* getTimer() { return this->timer; }
	void setPrintFPS(bool print_fps) { this->print_fps = print_fps; }
};

#endif