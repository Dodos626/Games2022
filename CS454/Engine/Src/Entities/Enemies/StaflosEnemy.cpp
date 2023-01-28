#include "StaflosEnemy.h"


StaflosEnemy::StaflosEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/StaflosConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->animator = new PlayerAnimator("Engine/Configs/enemy/StaflosAnimatorConfig.json", 0, { "staflos_move_left", "staflos_move_right", "staflos_attack_left", "staflos_attack_right", "staflos_idle_left", "staflos_idle_right"});
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
	
	int staflos_x = this->GetX();
	int staflos_y = this->GetY();
	int player_x = player.GetX();
	int player_y = player.GetY();

	bool can_move_right = this->tryMoveRight(staflos_x, staflos_y, this->GetWidth(), this->GetHeight());
	bool can_move_left = this->tryMoveLeft(staflos_x, staflos_y, this->GetWidth(), this->GetHeight());
	bool can_move_up = this->tryMoveUp(staflos_x, staflos_y, this->GetWidth(), this->GetHeight());
	bool can_move_down = this->tryMoveDown(staflos_x, staflos_y, this->GetWidth(), this->GetHeight());
	
	if (this->takes_damage) { // an exei pathei damage
		if (this->is_attacking) { // an ekana attack ekeini tin wra
			if(this->state == staflos_state::atack_left)
				this->state = staflos_state::move_left;
			else
				this->state = staflos_state::move_right;
			
			this->is_attacking = false;
			this->animator->StartForcedAnimation(0);
		}
		if (staflos_x > player_x) { // to attack irthe apo aristera
			if (can_move_up) // kai mporei na sinexisei
			{
				this->MoveUp(); // three times create a small 
				this->MoveUp(); // shaking effect
				this->MoveUp();
			}
			if (can_move_right) // kai mporei na sinexisei
				this->MoveRight();

		}
		else { // to attack irthe apo aristera
			if (can_move_up) // kai mporei na sinexisei
			{
				this->MoveUp();
				this->MoveUp();
				this->MoveUp();
			}
			if (can_move_left) // kai mporei na sinexisei
				this->MoveLeft();

		}
		return;
	}
	//ama mporei na baresei ton link ton baraei
	// alliws ama o link einai se 4 block apostasi
	// ton kinigaei kai krataei ligi apostasi
	// alliws meine akinitos
	
	int distance = abs(staflos_x - player_x);

	if (distance <= 16*this->view_distance) { // player within 4 blocks
		if (distance <= 25) { // if within attack range
			if (this->is_attacking || this->attack_cd > 0) { // if already attacking
				return;
			}
			if (player_x < staflos_x) // if player on my left
				this->state = staflos_state::atack_left;
			else
				this->state = staflos_state::atack_right;
			this->animator->changeAnimation(this->GetStateToInt(this->state));
			this->animator->StartForcedAnimation(3);
			this->is_attacking = true;
			if(staflos_y - player_y <= 16 && staflos_y - player_y >= -16) // an to y einai se attack range kane damage
				player.TakeDamage(this->damage, Point(staflos_x,staflos_y));
			this->attack_cd = 0.5;
		}
		else if(!this->is_attacking){ // if within range but not attack range
			if (player_x > staflos_x && can_move_right) { // o player einai pio deksia kai mporw na paw pio deksia
				
				this->state = staflos_state::move_right; // girna deksia
				
				this->MoveRight();
			}else if (player_x < staflos_x && can_move_left) { // o player einai pio aristera kai mporw na paw pio aristera
				this->state = staflos_state::move_left; // girna aristera
				this->MoveLeft();
			}
		}
	}
	else {
		if (static_cast<int>(this->state) % 2 == 0) {
			this->state = staflos_state::idle_left;
		}
		else {
			this->state = staflos_state::idle_right;
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
	else if (this->is_attacking) {
		if (this->state == staflos_state::atack_left) { // left attack
			if (this->animator->renderWholeAnimationWithFixFrame(this->GetX() - relative_x, this->GetY(), curr_time, -16, 0, 1)) {
				this->is_attacking = false;
				this->state = staflos_state::move_left;
			}
		}
		else {
			if (this->animator->renderWholeAnimationWithFixFrame(this->GetX() - relative_x, this->GetY(), curr_time, 0, 0, 0)) {
				this->is_attacking = false;
				this->state = staflos_state::move_right;
			}
		}
		
	}
	else {
		this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
	}

	if (!this->is_attacking && this->attack_cd > 0) {
		this->attack_cd -= curr_time;
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