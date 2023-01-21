#include "Timer.h"

Timer::Timer(double fps_ticker) {

	this->timer = al_create_timer(1.0 /fps_ticker);
	this->old_time = al_get_time();
}

void Timer::fps() {
	this->new_time = al_get_time();
	this->delta = this->new_time - this->old_time;
	double fps = 1 / this->delta;
	this->fps_timer += this->delta;
	this->avg_fps = (fps + this->avg_fps) / 2;
	
	if (this->fps_timer >= 1) {
		this->fps_timer = 0;
		if (this->print_fps)
			std::cout << "FPS: " << this->avg_fps << std::endl;
		this->avg_fps = 0;
		
	}
	this->old_time = this->new_time;
}

