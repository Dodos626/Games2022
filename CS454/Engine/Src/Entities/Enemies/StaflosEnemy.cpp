#include "StaflosEnemy.h"


StaflosEnemy::StaflosEnemy(Point* spawn) : Enemy(spawn, "Engine/Configs/enemy/StaflosConfig.json") {
	this->animator = new PlayerAnimator("Engine/Configs/enemy/StaflosAnimatorConfig.json", 0, { "staflos_move_left", "staflos_move_right", "staflos_attack_left", "staflos_attack_right" });
	this->name = "Staflos";
}


int StaflosEnemy::GetStateToInt(staflos_state state) {
	return static_cast<int>(state);
}


void StaflosEnemy::AI() {

}

void StaflosEnemy::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}
