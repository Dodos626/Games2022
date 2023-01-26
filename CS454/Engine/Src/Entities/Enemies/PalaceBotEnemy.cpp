#include "PalaceBotEnemy.h"

PalaceBotEnemy::PalaceBotEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/PalaceBotConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->name = "PalaceBot";
	
	this->animator = new PlayerAnimator("Engine/Configs/enemy/PalaceBotAnimatorConfig.json", 0, { "palaceBot_red", "palaceBot_blue", "palaceBot_cyan" });
}

void PalaceBotEnemy::AI(Point player_position) {
	//int x, int y, int width, int height
	if (moves_right) { // an paei deksia
		if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) { // kai mporei na sinexisei
			this->MoveRight();
		}
		else {
			moves_right = false;
		}
	}
	if (!moves_right) {
		if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight())) { // kai mporei na sinexisei
			this->MoveLeft();
		}
		else {
			moves_right = true;
		}
	}
}

void PalaceBotEnemy::Render(double curr_time, int relative_x) {
	this->animator->render(this->coordinates->GetX()- relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}


int PalaceBotEnemy::GetStateToInt(palaceBot_state state) {
	return static_cast<int>(state);
}