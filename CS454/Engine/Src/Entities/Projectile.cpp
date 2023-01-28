#include "Projectile.h"


Projectile::Projectile(Point* spawn, ProjectileDirection direction, Action tryMoveLeft_, Action tryMoveRight_) :
	tryMoveLeft(tryMoveLeft_),
	tryMoveRight(tryMoveRight_) {

	std::ifstream fin("Engine/Configs/enemy/ProjectileConfig.json");
	json data = json::parse(fin);
	this->direction = direction;
	this->location = spawn;
	this->speed = data["speed"];
	this->range = data["range"];
	this->width = data["width"];
	this->height = data["height"];
	this->damage = data["damage"];
	this->is_flying = true;
	fin.close();
	this->animator = new PlayerAnimator("Engine/Configs/enemy/ProjectileAnimatorConfig.json", GetStateToInt(direction), { "fly_left", "fly_right" });
	
}

void Projectile::AI(Player &player) {
	if (!this->is_flying) {
		return;
	}

	int player_x = player.GetX();
	int player_y = player.GetY();
	int projectile_x = this->GetX();
	int projectile_y = this->GetY();
	int player_h = player.GetHeight();
	int player_w = player.GetWidth();
	
	if (this->direction == ProjectileDirection::fly_left) { // an pame aristera
		for (int i = 0; i < this->speed; i++) {
			if (this->tryMoveLeft(this->GetX(), this->GetY(), this->width, this->height)) {
				this->MoveLeft();
				this->range -= 1;
				if (this->range == 0)
					this->Stop();
				// ean i arxi tu projectile einai anamesa stin aristeri kai deksia pleura tu paikti
				if ((player_x < projectile_x && projectile_x < player_x + player_w) && (player_y <= projectile_y && player_y + player_h >= projectile_y)) {
					player.TakeDamage(this->damage, Point(projectile_x, projectile_y));
					this->Stop();
				}
			}
			else {
				this->Stop();
			}
		}
		
	}
	else if (this->direction == ProjectileDirection::fly_right) {
		for (int i = 0; i < this->speed; i++) {
			if (this->tryMoveRight(this->GetX(), this->GetY(), this->width, this->height)) {
				this->MoveRight();
				this->range -= 1;
				if (this->range == 0)
					this->Stop();
				// ean to deksi kommati tu projectile einai meta tin arxi tu paikti kai i arxi tu projectile prin to telos tote eimaste mesa tu ston aksona x
				// ean to y tou paikti einai pio psila apo to projectile kai to projectile einai mesa ston paikti + to ipsos tu
				if ((projectile_x + 16 > player_x && projectile_x < player_x + 16) && (player_y <= projectile_y && player_y + player_h >= projectile_y)) {
					player.TakeDamage(this->damage, Point(projectile_x, projectile_y));
					this->Stop();
				}
			}
			else {
				this->Stop();
			}
		}
	}
	else {
		assert(false);
	}

}

void Projectile::Render(double curr_time, int relative_x) {
	if (!this->is_flying) {
		return;
	}
	this->animator->render(this->location->GetX() - relative_x, this->location->GetY(), curr_time, this->GetStateToInt(this->direction));
	
}

int Projectile::GetStateToInt(ProjectileDirection state) {
	return static_cast<int>(state);
}
