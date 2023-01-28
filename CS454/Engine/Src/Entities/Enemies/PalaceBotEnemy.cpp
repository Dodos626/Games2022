#include "PalaceBotEnemy.h"

PalaceBotEnemy::PalaceBotEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/PalaceBotConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->name = "PalaceBot";
	
	this->animator = new PlayerAnimator("Engine/Configs/enemy/PalaceBotAnimatorConfig.json", 0, { "palaceBot_red", "palaceBot_blue", "palaceBot_cyan" });
}

void PalaceBotEnemy::AI(Player& player) {
	if (this->takes_damage) {
		if (this->GetX() > player.GetX()) { // to attack irthe apo aristera
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
	//int x, int y, int width, int height
	if (moves_right) { // an paei deksia
		if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) && // kai mporei na sinexisei
			!this->tryMoveDown(this->GetX() + 16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveRight();
		}
		else {
			moves_right = false;
		}
	}
	if (!moves_right) {
		if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) && // kai mporei na sinexisei
			!this->tryMoveDown(this->GetX() + 16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveLeft();
		}
		else {
			moves_right = true;
		}
	}
}

void PalaceBotEnemy::Render(double curr_time, int relative_x) {
	if (this->takes_damage) {
		this->takes_damage = !this->animator->renderNframesOfAnimationWithFixFrame(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 1);
	}
	else {
		this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
	}
}


int PalaceBotEnemy::GetStateToInt(palaceBot_state state) {
	return static_cast<int>(state);
}


void PalaceBotEnemy::GetAttacked(int damage, Point point_of_attack) {
	if (!this->is_alive)
		return;
	this->health -= damage;
	this->takes_damage = true;
	this->SuffleAnimation();
	// Animate Damage
	if (this->health <= 0)
		this->_Death();
}

void PalaceBotEnemy::SuffleAnimation() {
	if (this->state == palaceBot_state::red) {
		this->state = palaceBot_state::blue;
	}
	else if (this->state == palaceBot_state::blue) {
		this->state = palaceBot_state::cyan;
	}
	else if (this->state == palaceBot_state::cyan) {
		this->state = palaceBot_state::red;
	}
}