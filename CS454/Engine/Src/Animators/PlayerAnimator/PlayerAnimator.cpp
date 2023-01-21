#include "PlayerAnimator.h"

PlayerAnimator::PlayerAnimator(std::string path, int curr_state) {
	
	//CREATE THE SPRITE SHEET
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->sprite_sheet = al_load_bitmap("Media/spriteSheet/link_sprite.png");
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

	this->number_of_animations = 23;

	this->curr_selected_animation = curr_state; //starting

	

	std::ifstream fin(path);
	json data = json::parse(fin);


	for (int i = 0; i < this->number_of_animations; i++) {
		this->registerSingleAnimation(data[p_stateToStr(static_cast<p_state>(i))]);
	}
	
}

void PlayerAnimator::selectAnimation(int animation_id) {
	this->resetCurrentAnimation();
	this->curr_selected_animation = animation_id;
}


void PlayerAnimator::registerSingleAnimation(json data) {
	this->animations.push_back(SingleAnimation(data));
}; 

void PlayerAnimator::render(int target_x, int target_y, double curr_time) {
	exit(EXIT_FAILURE);
}

void PlayerAnimator::render(int target_x, int target_y, double curr_time, int curr_state){
	
	if (curr_state != this->curr_selected_animation) {
		resetCurrentAnimation();
		this->curr_selected_animation = static_cast<int>(curr_state);
	}

	this->curr_mapping = this->animations.at(this->curr_selected_animation).getMapping(curr_time);
	al_draw_bitmap_region(this->sprite_sheet, this->curr_mapping.getX(), this->curr_mapping.getY(), this->curr_mapping.getWidth(), this->curr_mapping.getHeight(), target_x, target_y, 0);
}; 
