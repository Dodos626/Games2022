#include "GumaEnemy.h"

GumaEnemy::GumaEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/GumaConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->animator = new PlayerAnimator("Engine/Configs/enemy/GumaAnimatorConfig.json",0,animation_names);
	this->name = "Guma";
}


int GumaEnemy::GetStateToInt(guma_state state){
	return static_cast<int>(state);
}


void GumaEnemy::AI(Point player_position) {

}

void GumaEnemy::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}

