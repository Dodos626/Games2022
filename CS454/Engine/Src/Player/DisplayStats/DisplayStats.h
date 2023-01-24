#pragma once
#ifndef DISPLAY_STATS_INCLUDE
#define DISPLAY_STATS_INCLUDE

#include "../Player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "allegro5/allegro_primitives.h"


class DisplayStats {
private:
	int y_offset;
	int screen_width; 
	int screen_height;
	Player* player;
	ALLEGRO_BITMAP* display_box;
	
public:
	DisplayStats(int y_offset, int width, int height) {
		this->y_offset = y_offset;
		this->screen_width = width;
		this->screen_height = height;
		al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
		this->display_box = al_create_bitmap(width, y_offset);
		al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
		this->Precompute();
	};
	void Render();
	void Precompute(); // pre - renders boxes so the render only fills them

};

#endif