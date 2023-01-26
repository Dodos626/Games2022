#include "PalaceBotEnemy.h"

PalaceBotEnemy::PalaceBotEnemy(Point* spawn) : Enemy(spawn, "Engine/Configs/enemy/PalaceBotConfig.json") {
	this->name = "PalaceBot";
	
	this->animator = new PlayerAnimator("Engine/Configs/enemy/PalaceBotAnimatorConfig.json", 0, { "palaceBot_red", "palaceBot_blue", "palaceBot_cyan" });
}

void PalaceBotEnemy::AI() {

}

void PalaceBotEnemy::Render(double curr_time) {
	this->animator->render(this->coordinates->GetX(), this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}


int PalaceBotEnemy::GetStateToInt(palaceBot_state state) {
	return static_cast<int>(state);
}