#pragma once
#ifndef DISPLAY_STATS_INCLUDE
#define DISPLAY_STATS_INCLUDE

#include "../Player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "allegro5/allegro_primitives.h"

class Player;

class DisplayStats {
private:
	int screen_width; 
	int screen_height;
	Player* player;
	ALLEGRO_BITMAP* display_box;
	
public:
	DisplayStats(Player &player, int width, int height, int y_offset);
	void Render();
	void Precompute(); // pre - renders boxes so the render only fills them
	
};

#endif