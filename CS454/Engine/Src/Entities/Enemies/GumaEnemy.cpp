#include "GumaEnemy.h"

GumaEnemy::GumaEnemy(Point *spawn) : Enemy(spawn, "Engine/Configs/enemy/GumaConfig.json") {
	this->animator = new PlayerAnimator("Engine/Configs/enemy/GumaAnimatorConfig.json",0,animation_names);
	this->name = "Guma";
}


int GumaEnemy::GetStateToInt(guma_state state){
	return static_cast<int>(state);
}


void GumaEnemy::AI() {

}

void GumaEnemy::Render(double curr_time) {
	this->animator->render(this->coordinates->GetX(), this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}

