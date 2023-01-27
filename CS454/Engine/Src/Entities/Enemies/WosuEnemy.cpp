#include "WosuEnemy.h"

WosuEnemy::WosuEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/WosuConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->name = "Wosu";
	this->animator = new PlayerAnimator("Engine/Configs/enemy/WosuAnimatorConfig.json", 0, { "move_left","move_right"});
}

void WosuEnemy::AI(Point player_position) {
	if (this->takes_damage) {
		if (this->GetX() > player_position.GetX()) { // to attack irthe apo aristera
			if (this->tryMoveUp(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) // kai mporei na sinexisei
			{
				this->MoveUp(); // three times create a small 
				this->MoveUp(); // shaking effect
				this->MoveUp();
			}
			if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) // kai mporei na sinexisei
				this->MoveRight();
			
		}
		else { // to attack irthe apo aristera
			if (this->tryMoveUp(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) // kai mporei na sinexisei
			{
				this->MoveUp();
				this->MoveUp(); 
				this->MoveUp();
			}
			if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) // kai mporei na sinexisei
				this->MoveLeft();
			
		}
		return;
	}
	if (this->state == wosu_state::move_right) { // an paei deksia
		if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) && // kai mporei na sinexisei
			!this->tryMoveDown(this->GetX()+16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveRight();
		}
		else {
			this->state = wosu_state::move_left;
		}
	}
	if (this->state == wosu_state::move_left) {
		if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) // kai mporei na sinexisei
			&& !this->tryMoveDown(this->GetX() - 16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveLeft();
		}
		else {
			this->state = wosu_state::move_right;
		}
	}
}

void WosuEnemy::Render(double curr_time, int relative_x) {
	if (this->takes_damage) {
		this->takes_damage = !this->animator->renderNframesOfAnimationWithFixFrame(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 1);
	}
	else {
		this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
	}
	
}

int WosuEnemy::GetStateToInt(wosu_state state) {
	return static_cast<int>(state);
}


void WosuEnemy::ChangeDirection() {
	if (this->state == wosu_state::move_left) {
		this->state = wosu_state::move_right;
	}
	else {
		this->state = wosu_state::move_left;
	}
}