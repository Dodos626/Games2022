#include "WosuEnemy.h"

WosuEnemy::WosuEnemy(Point* spawn) : Enemy(spawn, "Engine/Configs/enemy/WosuConfig.json") {
	this->name = "Wosu";
	this->animator = new PlayerAnimator("Engine/Configs/enemy/WosuAnimatorConfig.json", 0, { "move_left","move_right"});
}

void WosuEnemy::AI() {

}

void WosuEnemy::Render(double curr_time) {
	this->animator->render(this->coordinates->GetX(), this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
}

int WosuEnemy::GetStateToInt(wosu_state state) {
	return static_cast<int>(state);
}