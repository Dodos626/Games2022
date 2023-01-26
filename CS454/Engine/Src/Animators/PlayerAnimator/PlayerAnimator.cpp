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

bool PlayerAnimator::renderAttack(int target_x, int target_y, double curr_time, int curr_state) {

	Mappings *next_mapping = this->animations.at(this->curr_selected_animation)->getMapping(curr_time); // take next mapping

	if ( this->curr_mapping->getX() != next_mapping->getX() || this->curr_mapping->getY() != next_mapping->getY()) { // if the next mapping is different
		
		this->total_animation_frames -= 1;

		std::cout << "remaining frames : " << this->total_animation_frames << std::endl;
	}
	

	int fix_x = 0;
	// the curr_state is fixed to 11 for right attack and 10 for left attack and crouch left attack is 12
	//so we can reuse this function in crouch attack right without mendling with it's x
	if (this->total_animation_frames == 2 && curr_state  == 11) { 
		fix_x = -16; //first frame of right attack needs to render 16 pixels to the left
	}
	else if (this->total_animation_frames <= 1 && (curr_state == 10 || curr_state == 12)) { 
		fix_x = -16; // last frame of left attack and left crouch attack needs to render 16 pixels to the left
	}
	
	if(this->total_animation_frames != 0) // the last frame will be repeating the first frame
		this->curr_mapping = next_mapping; // in order to hack it we extend the attack for 1 more render
	

	al_draw_bitmap_region(this->sprite_sheet, this->curr_mapping->getX(), this->curr_mapping->getY(), this->curr_mapping->getWidth(), this->curr_mapping->getHeight(), target_x + fix_x, target_y, 0);

	if (this->total_animation_frames == 0) {
		return true;
	}
	else {
		return false;
	}
};