#include "SingleAnimation.h"


SingleAnimation::SingleAnimation(json data) {
	this->frame_duration = data["animation_time"];
	this->number_of_frames = data["number_of_frames"];
	this->registerMappings(data["mappings"]);
}

void SingleAnimation::registerMappings(json data) {
	for (int i = 0; i < this->number_of_frames; i++) {
		Mappings curr_mapping = Mappings(data[i]["x"], data[i]["y"], data[i]["width"], data[i]["height"]);
		this->mappings.push_back(curr_mapping);
	} 
}

void SingleAnimation::progressAnimation() {
	if (this->curr_selected_frame < this->number_of_frames - 1)
		this->curr_selected_frame++;
	else
		this->curr_selected_frame = 0;
}

Mappings SingleAnimation::getMapping(double current_time) {
	
	Mappings curr_mappings = this->mappings.at(this->curr_selected_frame); //take the current animation position
	

	
	this->total_time_passed += current_time;
	if (this->total_time_passed > (this->frame_duration/this->number_of_frames)) { // if the time has passed
		
		
		this->progressAnimation(); // progress the animation
		curr_mappings = this->mappings.at(this->curr_selected_frame); // take the new one
		this->total_time_passed = 0; // update the last time
	}
	
	
	
	return curr_mappings; // return the current one
};