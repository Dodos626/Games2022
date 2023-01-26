#pragma once
#ifndef PLAYER_ANIMATOR_INCLUDE
#define PLAYER_ANIMATOR_INCLUDE

#include "../Animator.h"

#include <vector>

class PlayerAnimator :  public Animator {
private:
	void registerSingleAnimation(json data); // register the animations (from json)
	int total_animation_frames = 0; // used only on forced animations
public:
	PlayerAnimator(std::string path, int curr_state, std::vector<std::string> animation_names);
	void render(int target_x, int target_y, double curr_time, int curr_state); // render the right animations->mapping
	void selectAnimation(int animation_id);
	bool renderAttack(int target_x, int target_y, double curr_time, int curr_state);
	
	// the + 1 part is because if we need 2 frames, we need to render the first frame 
	// and then the second frame till the end which will happen when frame 3 will come up
	void StartForcedAnimation(int total_animation_frames){
		this->total_animation_frames = total_animation_frames + 1;
	} 
};

#endif