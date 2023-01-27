#include "StaflosEnemy.h"


StaflosEnemy::StaflosEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/StaflosConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->animator = new PlayerAnimator("Engine/Configs/enemy/StaflosAnimatorConfig.json", 0, { "staflos_move_left", "staflos_move_right", "staflos_attack_left", "staflos_attack_right" });
	this->name = "Staflos";
}


int StaflosEnemy::GetStateToInt(staflos_state state) {
	return static_cast<int>(state);
}


void StaflosEnemy::AI(Point player_position) {
	//blepei ama trwei attack den kanei attack
	//ama mporei na baresei ton link ton baraei
	// alliws ama o link einai se 4 block apostasi
	// ton kinigaei kai krataei ligi apostasi
	// alliws meine akinitos
	

}

void StaflosEnemy::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}

void StaflosEnemy::ChangeDirection() { // cannot change direction if attacking
	if (this->state == staflos_state::move_left) { this->state = staflos_state::move_right; }
	else if (this->state == staflos_state::move_right) { this->state = staflos_state::move_left; }
};