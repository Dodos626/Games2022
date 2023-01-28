#include "Projectile.h"


Projectile::Projectile(Point* spawn, ProjectileDirection direction, Action tryMoveLeft_, Action tryMoveRight_) :
	tryMoveLeft(tryMoveLeft_),
	tryMoveRight(tryMoveRight_) {

	std::ifstream fin("Engine/Configs/enemy/ProjectileConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;
	this->direction = direction;
	this->animator = new PlayerAnimator("Engine/Configs/enemy/ProjectileAnimatorConfig.json", 0, {"fly_left", "fly_right"});
	this->speed = data["speed"];
	this->range = data["range"];
	this->width = data["width"];
	this->height = data["height"];
	this->damage = data["damage"];
	this->is_flying = true;
}

void Projectile::AI(Player &player) {

	if (!this->is_flying)
		return;
	int pl_ux = player.GetX();
	int pl_ly = player.GetY();
	int pl_width = player.GetWidth();
	int pl_height = player.GetHeight();
	Point pl(pl_ux, pl_ly);

	int p_ux = this->GetX();
	int p_ly = this->GetY();
	int p_width = this->width;
	int p_height = this->height;
	for (int i = 0; i < this->speed; i++) {

		if (this->range == 0) {
			this->is_flying = false;
			break;
		}
		this->range -= 1;
		if (this->direction == ProjectileDirection::fly_right) {
			if (this->tryMoveRight(this->GetX(), this->GetY(), this->width, this->height)) {
				this->MoveRight();
			}
			else {
				this->is_flying = false;
				break;
			}
			
		}
		else {
			if (this->tryMoveLeft(this->GetX(), this->GetY(), this->width, this->height)) {
				this->MoveLeft();
			}
			else {
				this->is_flying = false;
				break;
			}

		}
		p_ux = this->GetX();
		Point ul(p_ux, p_ly);
		Point dl(p_ux, p_ly + p_height);
		Point ur(p_ux + p_width, p_ly);
		Point dr(p_ux + p_width, p_ly + p_height);
		if (pl.InRectangle(ul, pl_width, pl_height) || pl.InRectangle(dl, pl_width, pl_height) || pl.InRectangle(ur, pl_width, pl_height) || pl.InRectangle(dr, pl_width, pl_height))
		{
			player.TakeDamage(this->damage, *this->location); 
			this->is_flying = false;
			break;
		}
	}
}

void Projectile::Render(double curr_time, int relative_x) {
	if(this->is_flying)
		this->animator->render(this->location->GetX() - relative_x, this->location->GetY(), curr_time, this->GetStateToInt(this->direction));
	
}

int Projectile::GetStateToInt(ProjectileDirection state) {
	return static_cast<int>(state);
}
