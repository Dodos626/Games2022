#pragma once
#ifndef ANIMATOR_INCLUDE
#define ANIMATOR_INCLUDE

#include <allegro5/allegro.h>
#include "SingleAnimation/SingleAnimation.h"
#include <vector>

class Animator {
protected:
	ALLEGRO_BITMAP* sprite_sheet; // the sprite sheet
	
	int number_of_animations; // how many animations there are
	
	int curr_selected_animation; // the current animation

	Mappings *curr_mapping; // the current mapping
	
	std::vector<SingleAnimation *> animations; // the animations, every one corresponds to one animation

	virtual void registerSingleAnimation(json data) = 0; // register the animations (from json)
	
public:
	//destructor
	~Animator() {
		for (int i = 0; i < this->animations.size(); i++)
			delete this->animations.at(i);
		al_destroy_bitmap(this->sprite_sheet);
	}
	//VIRTUAL
	virtual void render(int target_x, int target_y, double curr_time, int curr_state) = 0; // render the right animations->mapping
	virtual void selectAnimation(int animation_id) = 0;


	//implemented
	void resetAllAnimation() {
		for (int i = 0; i < this->number_of_animations; i++) {
			this->animations.at(i)->resetAnimation();
		}
	}
	void resetCurrentAnimation() {
		this->animations.at(this->curr_selected_animation)->resetAnimation();
	}
	int getWidth() { return this->curr_mapping->getWidth(); };

	// changes the animation to the corresponding id
	void changeAnimation(int id) {
		this->resetAllAnimation();
		this->curr_selected_animation = id;
	}
};

#endif