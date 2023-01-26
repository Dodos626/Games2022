#include "PlayerAnimator.h"

PlayerAnimator::PlayerAnimator(std::string path, int curr_state, std::vector<std::string> animation_names) {

	std::ifstream fin(path);
	json data = json::parse(fin);


	std::string sprite_sheet_path = data["sprite_sheet_path"];
	
	//CREATE THE SPRITE SHEET
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->sprite_sheet = al_load_bitmap(sprite_sheet_path.c_str());
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

	this->number_of_animations = data["total_animations"];

	this->curr_selected_animation = curr_state; //starting

	assert(this->number_of_animations == animation_names.size());

	


	for (int i = 0; i < this->number_of_animations; i++) {
		this->registerSingleAnimation(data[animation_names.at(i)]);
	}
	
}

void PlayerAnimator::selectAnimation(int animation_id) {
	this->resetCurrentAnimation();
	this->curr_selected_animation = animation_id;
}


void PlayerAnimator::registerSingleAnimation(json data) {
	this->animations.push_back(new SingleAnimation(data));
}; 



void PlayerAnimator::render(int target_x, int target_y, double curr_time, int curr_state){
	if (curr_state != this->curr_selected_animation) {
		this->selectAnimation(curr_state);
	}
	this->curr_mapping = this->animations.at(this->curr_selected_animation)->getMapping(curr_time);
	al_draw_bitmap_region(this->sprite_sheet, this->curr_mapping->getX(), this->curr_mapping->getY(), this->curr_mapping->getWidth(), this->curr_mapping->getHeight(), target_x, target_y, 0);
}; 




bool PlayerAnimator::renderWholeAnimationWithFixFrame(int target_x, int target_y, double curr_time, int fix_x_amount, int fix_y_amount, int frame_to_fix) {
	Mappings* next_mapping = this->animations.at(this->curr_selected_animation)->getMapping(curr_time); // take next mapping

	if (this->curr_mapping->getX() != next_mapping->getX() || this->curr_mapping->getY() != next_mapping->getY()) { // if the next mapping is different

		this->total_animation_frames -= 1;

		std::cout << "remaining frames : " << this->total_animation_frames << std::endl;
	}

	if (this->total_animation_frames != 0) // the last frame will be repeating the first frame
		this->curr_mapping = next_mapping; // in order to hack it we extend the attack for 1 more render


	// if we are at the frame that needs fix
	// or if we are on the hack frame and the frame to fix was the previous that we hold for 1 more render
	if (this->total_animation_frames == frame_to_fix || (this->total_animation_frames == 0 && frame_to_fix == 1)){
		al_draw_bitmap_region(this->sprite_sheet, this->curr_mapping->getX(), this->curr_mapping->getY(), this->curr_mapping->getWidth(), this->curr_mapping->getHeight(), target_x + fix_x_amount, target_y + fix_y_amount, 0);
	}
	else {
		al_draw_bitmap_region(this->sprite_sheet, this->curr_mapping->getX(), this->curr_mapping->getY(), this->curr_mapping->getWidth(), this->curr_mapping->getHeight(), target_x, target_y, 0);
	}

	

	if (this->total_animation_frames == 0) {
		return true;
	}
	else {
		return false;
	}
}


// fix_x_amount , frame_of_fix