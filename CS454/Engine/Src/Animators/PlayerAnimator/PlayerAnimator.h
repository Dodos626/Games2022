#pragma once
#ifndef PLAYER_ANIMATOR_INCLUDE
#define PLAYER_ANIMATOR_INCLUDE

#include "../Animator.h"

#include <vector>

class PlayerAnimator :  public Animator {
private:
	void registerSingleAnimation(json data); // register the animations (from json)
public:
	PlayerAnimator(std::string path, int curr_state, std::vector<std::string> animation_names);
	void render(int target_x, int target_y, double curr_time, int curr_state); // render the right animations->mapping
	void selectAnimation(int animation_id);
	void render(int target_x, int target_y, double curr_time);
};

#endif