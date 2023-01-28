#include "DisplayStats.h"

DisplayStats::DisplayStats(Player& player, int width, int height, int y_offset) {
	this->player = &player;
	this->screen_width = width;
	this->screen_height = height;
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->display_box = al_create_bitmap(width, y_offset);
	this->display_message = al_create_bitmap(width / 2, 10);
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	this->box_y_offset = y_offset / 2;

	this->Precompute();
}


void DisplayStats::Render(double curr_time) {
	if (this->time > 0) {
		this->time -= curr_time;
		al_draw_bitmap(this->display_message, this->screen_width / 4, this->screen_height - 10, 0);
	}
	al_draw_bitmap(this->display_box, 0, this->screen_height , 0);
};


void DisplayStats::Precompute() {
	this->font = al_create_builtin_font();

	al_set_target_bitmap(this->display_box);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	int max_health = this->player->max_health;
	int max_mana = this->player->max_mana;


	this->max_health_boxes = max_health / 20;
	this->max_mana_boxes = max_mana / 50;
	
	

	
	int offset_x = this->screen_width / 4;


	this->health_box_x_offset = offset_x;
	this->mana_box_x_offset = 10 + offset_x * 2;
	

	al_draw_text(this->font, al_map_rgb(255, 255, 255), 5, 3, 0, "Lives");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), offset_x, 3, 0, "Health");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), 10 + offset_x*2, 3, 0, "Mana");
	al_draw_text(this->font, al_map_rgb(255, 255, 255), 15 + offset_x*3, 3, 0, "Points");
	
	
	
};

void DisplayStats::CreateBoxes(int starting_x, int number_of_boxes) {

	for (int box_number = 0; box_number < number_of_boxes; box_number++) {
		al_draw_filled_rectangle(
			starting_x + box_number *(this->margin+this->box_size), // x => starting_x + box_number * ( margin_from_previous_box + box_size)
			this->box_y_offset, //y is fixed
			starting_x + box_number * (this->margin + this->box_size) + this->box_size, // max x = starting_x +  box_number * ( margin_from_previous_box + box_size) + box_size
			this->box_y_offset + this->box_size,  // max y = y + box_size
			al_map_rgb(255, 255, 255)  // color
		);
	}
	
}

void DisplayStats::FillBoxes(int starting_x, int player_stat, int stat_per_box, ALLEGRO_COLOR color ) {
	
	if (player_stat < 0) { return; }

	for (int box_number = 0; box_number < (player_stat / stat_per_box); box_number++) {
		int this_box_start_x = starting_x + box_number * (this->margin + this->box_size); // this_box_start_x = starting_x + box_number * ( margin_from_previous_box + box_size)
		al_draw_filled_rectangle(
			this_box_start_x + 1, // starting x
			this->box_y_offset + 1, // y is fixed
			this_box_start_x + this->box_size - 1, // max x = starting x + box_size - 1
			this->box_y_offset + this->box_size - 1, // max y = y + box_size - 1
			color //color
		);
	}

	int remaining_stat = player_stat % stat_per_box; // last box remaining life

	if (remaining_stat != 0) { //if life isn't full
		int empty_box_x = player_stat / stat_per_box;  // the first empty block of life
		al_draw_filled_rectangle(
			1 + starting_x + empty_box_x * (this->margin + this->box_size),
			1 + this->box_y_offset,
			starting_x + empty_box_x * (this->margin + this->box_size) + remaining_stat / (stat_per_box/10),
			this->box_y_offset + this->box_size - 1, // max y = y + box_size - 1
			color
		);
	}


};



void DisplayStats::PrepareStats() {
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	al_set_target_bitmap(this->display_box);
	this->CreateBoxes(this->health_box_x_offset, this->max_health_boxes);
	this->CreateBoxes(this->mana_box_x_offset, this->max_mana_boxes);
	this->FillBoxes(this->health_box_x_offset, this->player->health, 20, al_map_rgb(255, 51, 51));
	this->FillBoxes(this->mana_box_x_offset, this->player->mana, 50, al_map_rgb(51, 255, 255));


	//temporary solution because the letters where stacking on each other
	al_draw_filled_rectangle(5, this->box_y_offset, this->health_box_x_offset - 10, 30, al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(15 + this->health_box_x_offset * 3, this->box_y_offset, 115 + this->health_box_x_offset * 3, 30, al_map_rgb(0, 0, 0));
	
	al_draw_text(this->font, al_map_rgb(255, 255, 255), 5, this->box_y_offset, 0, std::to_string(this->player->lives).c_str());
	al_draw_text(this->font, al_map_rgb(255, 255, 255), 15 + this->health_box_x_offset*3, this->box_y_offset, 0, std::to_string(this->player->points).c_str());

	if (this->time > 0) {
		al_set_target_bitmap(this->display_message);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(this->font, al_map_rgb(255, 255, 255), 5, 2 , 0, this->message.c_str());
	}
	
	
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	//this->DisplayScore();
	//this->DisplayLives();
};


DisplayStats::~DisplayStats() {
	al_destroy_bitmap(this->display_box);
	al_destroy_font(this->font);
}