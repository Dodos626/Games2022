#include "WosuEnemy.h"

WosuEnemy::WosuEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/WosuConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->name = "Wosu";
	this->animator = new PlayerAnimator("Engine/Configs/enemy/WosuAnimatorConfig.json", 0, { "move_left","move_right"});
}

void WosuEnemy::AI(Point player_position) {
	if (this->state == wosu_state::move_right) { // an paei deksia
		if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) { // kai mporei na sinexisei
			this->MoveRight();
		}
		else {
			this->state = wosu_state::move_left;
		}
	}
	if (this->state == wosu_state::move_left) {
		if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) { // kai mporei na sinexisei
			this->MoveLeft();
		}
		else {
			this->state = wosu_state::move_right;
		}
	}
}

void WosuEnemy::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX()-relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}

int WosuEnemy::GetStateToInt(wosu_state state) {
	return static_cast<int>(state);
}