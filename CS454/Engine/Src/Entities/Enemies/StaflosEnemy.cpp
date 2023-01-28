#include "StaflosEnemy.h"


StaflosEnemy::StaflosEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/StaflosConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->animator = new PlayerAnimator("Engine/Configs/enemy/StaflosAnimatorConfig.json", 0, { "staflos_move_left", "staflos_move_right", "staflos_attack_left", "staflos_attack_right" });
	this->name = "Staflos";
}


int StaflosEnemy::GetStateToInt(staflos_state state) {
	return static_cast<int>(state);
}
/*
enum class staflos_state {
	move_left,
	move_right,
	atack_left,
	atack_right
};*/

void StaflosEnemy::AI(Player& player) {
	//blepei ama trwei attack den kanei attack
	//ama mporei na baresei ton link ton baraei
	// alliws ama o link einai se 4 block apostasi
	// ton kinigaei kai krataei ligi apostasi
	// alliws meine akinitos
	
	if (this->takes_damage) { // an exei pathei damage
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
	if (this->state == staflos_state::move_right) { // an paei deksia
		if (this->tryMoveRight(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) && // kai mporei na sinexisei
			!this->tryMoveDown(this->GetX() + 16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveRight();
		}
		else {
			this->state = staflos_state::move_left;
		}
	}
	if (this->state == staflos_state::move_left) {
		if (this->tryMoveLeft(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight()) && // kai mporei na sinexisei
			!this->tryMoveDown(this->GetX() + 16, this->GetY(), this->GetWidth(), this->GetHeight())) { // xwris na pesei
			this->MoveLeft();
		}
		else {
			this->state = staflos_state::move_right;
		}
	}
}

void StaflosEnemy::Render(double curr_time, int relative_x) {
	if (this->immunity > 0) {
		this->immunity -= curr_time;
	}
	if (this->takes_damage) {
		this->takes_damage = !this->animator->renderNframesOfAnimationWithFixFrame(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 1);
	}
	else {
		this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
	}
}

void StaflosEnemy::ChangeDirection() { // cannot change direction if attacking
	if (this->immunity > 0) { return; }
	this->immunity = 0.5;
	if (this->state == staflos_state::move_left) { this->state = staflos_state::move_right; }
	else if (this->state == staflos_state::move_right) { this->state = staflos_state::move_left; }
};


void StaflosEnemy::GetAttacked(int damage, Point point_of_attack) {
	if (!this->is_alive)
		return;
	
	int attack_x = point_of_attack.GetX();
	int attack_y = point_of_attack.GetY();

	int my_state = static_cast<int>(this->state);
	
	std::cout << attack_y << " " << this->GetY() << "\n";
	if ((attack_y > this->GetY())|| //ean trwei crouch attack 
		((my_state % 2 == 1)&&(attack_x < this->GetX())) || // ama koitaei deksia kai trwei apo aristera
		((my_state % 2 == 0) && (attack_x > this->GetX()))) { // ama koitaei aristera kai trwei apo deksia
		this->health -= damage;
		this->takes_damage = true;
		// Animate Damage
		if (this->health <= 0)
			this->_Death();
	}
}