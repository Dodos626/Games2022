#include "DisplayStats.h"

DisplayStats::DisplayStats(Player& player, int width, int height, int y_offset) {
	this->player = &player;
	this->screen_width = width;
	this->screen_height = height;
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->display_box = al_create_bitmap(width, y_offset);
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	this->box_y_offset = y_offset / 2;

	this->Precompute();
}


void DisplayStats::Render() {
	int max_health = this->player->max_health;
	int max_mana = this->player->max_mana;
	int mana = this->player->mana;
	int health = this->player->health;
	int points = this->player->points;
	int lives = this->player->lifes;


	int max_health_boxes = max_health / 20;
	int max_mana_boxes = max_mana / 40;

	al_draw_bitmap(this->display_box, 0, this->screen_height , 0);
};


void DisplayStats::Precompute() {
	ALLEGRO_FONT* font = al_create_builtin_font();

	al_set_target_bitmap(this->display_box);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	int max_health = this->player->max_health;
	int max_mana = this->player->max_mana;


	int max_health_boxes = max_health / 20;
	int max_mana_boxes = max_mana / 40;
	
	

	
	int offset_x = this->screen_width / 4;
	std::cout << this->screen_width << ": screen , offset_X : " << offset_x <<std::endl;


	this->health_box_x_offset = offset_x;
	this->mana_box_x_offset = 10 + offset_x * 2;
	

	al_draw_text(font, al_map_rgb(255, 255, 255), 0, 3, 0, "Lives");
	al_draw_text(font, al_map_rgb(255, 255, 255), offset_x, 3, 0, "Health");
	al_draw_text(font, al_map_rgb(255, 255, 255), 10 + offset_x*2, 3, 0, "Mana");
	al_draw_text(font, al_map_rgb(255, 255, 255), 15 + offset_x*3, 3, 0, "Points");

	al_draw_rectangle(this->health_box_x_offset, this->box_y_offset, this->health_box_x_offset + 10 , this->box_y_offset + 10, al_map_rgb(255, 255, 255), 1);
};