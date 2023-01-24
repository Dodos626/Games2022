#pragma once
#ifndef DISPLAY_STATS_INCLUDE
#define DISPLAY_STATS_INCLUDE

#include "../Player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "allegro5/allegro_primitives.h"
#include <string>
class Player;

class DisplayStats {
private:
	int screen_width; 
	int screen_height;
	int health_box_x_offset, max_health_boxes;
	int mana_box_x_offset, max_mana_boxes;
	int box_y_offset;
	int box_size = 11;
	Player* player;
	ALLEGRO_BITMAP* display_box;
	ALLEGRO_FONT* font;

	int margin = 2; // from box to box the offset
	

	void FillBoxes(int starting_x, int player_stat, int stat_per_box, ALLEGRO_COLOR color);
	void CreateBoxes(int starting_x, int number_of_boxes);

	
public:
	DisplayStats(Player &player, int width, int height, int y_offset);
	~DisplayStats();
	void PrepareStats();
	void Render();
	void Precompute(); // pre - renders boxes so the render only fills them
	
};

#endif