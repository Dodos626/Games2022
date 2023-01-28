#include "GumaEnemy.h"

GumaEnemy::GumaEnemy(Point* spawn, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_) : Enemy(spawn, "Engine/Configs/enemy/GumaConfig.json", tryMoveLeft_, tryMoveRight_, tryMoveUp_, tryMoveDown_){
	this->animator = new PlayerAnimator("Engine/Configs/enemy/GumaAnimatorConfig.json",0,animation_names);
	this->name = "Guma";
}


int GumaEnemy::GetStateToInt(guma_state state){
	return static_cast<int>(state);
}


void GumaEnemy::AI(Player& player) {

	int guma_x = this->GetX();
	int guma_y = this->GetY();
	int player_x = player.GetX();
	int player_y = player.GetY();

	bool can_move_right = this->tryMoveRight(guma_x, guma_y, this->GetWidth(), this->GetHeight());
	bool can_move_left = this->tryMoveLeft(guma_x, guma_y, this->GetWidth(), this->GetHeight());
	bool can_move_up = this->tryMoveUp(guma_x, guma_y, this->GetWidth(), this->GetHeight());
	bool can_move_down = this->tryMoveDown(guma_x, guma_y, this->GetWidth(), this->GetHeight());

	this->ClearProjectiles(); // clear all projectiles that u need
	this->AiProjectile(player); // make ai move

	
	if (this->takes_damage) { // an exei pathei damage
		if (guma_x > player_x) { // to attack irthe apo aristera
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

	int distance = abs(guma_x - player_x);
	if (distance <= 16 * this->view_distance) { // player within view distance
		
		
		if ( distance > 80) { // if enemy far enough to cast a projectile
			if (this->is_attacking || this->attack_cd > 0) { // if already attacking
				return;
			}
			if (player_x < guma_x) // if player on my left
				this->state = guma_state::atack_left;
			else
				this->state = guma_state::atack_right;
			this->animator->changeAnimation(this->GetStateToInt(this->state));
			this->animator->StartForcedAnimation(1);
			this->is_attacking = true;
			this->SpawnProjectile(this->state);
			this->attack_cd = 0.5;
		}
		else if (!this->is_attacking) { // if too close
			if (player_x > guma_x && can_move_left) { // o player einai pio deksia kai mporw na paw pio aristera

				this->state = guma_state::move_left; // girna aristera

				this->MoveLeft(); // kai apofige ton
			}
			else if (player_x < guma_x && can_move_right) { // o player einai pio aristera kai mporw na paw pio deksia
				this->state = guma_state::move_right; // girna deksia
				this->MoveRight(); // kai apofige ton
			} 
			/*
			else if (!this->takes_damage){ // cant escape attack link
				std::cout << " mpike edw \n";
				if (this->is_attacking || this->attack_cd > 0) { // if already attacking
					return;
				}
				if (player_x < guma_x) // if player on my left
					this->state = guma_state::atack_left;
				else
					this->state = guma_state::atack_right;
				this->animator->changeAnimation(this->GetStateToInt(this->state));
				this->animator->StartForcedAnimation(1);
				this->is_attacking = true;
				this->SpawnProjectile(this->state);
				this->attack_cd = 0.5;
			}*/
		}
	}
	else { //player nowhere to be found
		if (static_cast<int>(this->state) % 2 == 0) {
			this->state = guma_state::idle_left;
		}
		else {
			this->state = guma_state::idle_right;
		}
	}
	
}


void GumaEnemy::Render(double curr_time, int relative_x) {
	
	if (this->immunity > 0) {
		this->immunity -= curr_time;
	}
	if (this->takes_damage) {
		this->takes_damage = !this->animator->renderNframesOfAnimationWithFixFrame(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, 1);
	}
	else if (this->is_attacking) {
		if (this->state == guma_state::atack_left) { // left attack
			if (this->animator->renderWholeAnimationWithFixFrame(this->GetX() - relative_x, this->GetY(), curr_time, 0, 0, 0)) {
				this->is_attacking = false;
				this->state = guma_state::idle_left;
			}
		}
		else {
			if (this->animator->renderWholeAnimationWithFixFrame(this->GetX() - relative_x, this->GetY(), curr_time, 0, 0, 0)) {
				this->is_attacking = false;
				this->state = guma_state::idle_right;
			}
		}

	}
	else {
		this->animator->render(this->coordinates->GetX() - relative_x, this->coordinates->GetY(), curr_time, this->GetStateToInt(this->state));
	}

	if (!this->is_attacking && this->attack_cd > 0) {
		this->attack_cd -= curr_time;
	}
	this->RenderProjectile(curr_time, relative_x);
}

void GumaEnemy::SpawnProjectile(guma_state state) {
	//std::cout << this->GetX() << " " << this->GetY() << std::endl;
	//224 176
	if(static_cast<int>(state)%2 == 0) // koitaei aristera
		this->projectiles.push_back(new Projectile(new Point(this->GetX(), this->GetY()), ProjectileDirection::fly_left, tryMoveLeft, tryMoveRight));
	else
		this->projectiles.push_back(new Projectile(new Point(this->GetX(), this->GetY()), ProjectileDirection::fly_right, tryMoveLeft, tryMoveRight));

	
};


void GumaEnemy::RenderProjectile(double curr_time, int relative_x) {
	
	for (int i = 0; i < this->projectiles.size(); i++)
		this->projectiles[i]->Render(curr_time, relative_x);

};
void GumaEnemy::AiProjectile(Player& player) {
	for (int i = 0; i < this->projectiles.size(); i++)
		this->projectiles[i]->AI(player);
};


void GumaEnemy::ClearProjectiles() {
	std::vector<Projectile*>::iterator iter;
	for (iter = this->projectiles.begin(); iter != this->projectiles.end(); ) {
		if ((*iter)->isFlying() == false)
			iter = this->projectiles.erase(iter);
		else
			++iter;
	}

};