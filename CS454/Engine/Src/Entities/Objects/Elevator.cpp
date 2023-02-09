#include "Elevator.h"


Elevator::Elevator(Point* location, Point *stop_location, ElevatorStatus status) {
	std::ifstream fin("Engine/Configs/object/ElevatorAnimatorConfig.json");
	
	json data = json::parse(fin);
	this->speed = data["speed"];
	this->coordinates = location;
	this->initial_location = new Point(location->GetX(), location->GetY());
	this->stop_location = stop_location;
	this->status = status;
	this->name = "elevator";
	this->width = data["width"];
	this->height = data["height"];
	assert(this->coordinates->GetX() == this->stop_location->GetX());
	fin.close();
	this->animator = new PlayerAnimator("Engine/Configs/object/ElevatorAnimatorConfig.json", 0, { "elevator" });
}

void Elevator::AI(Player& player) {
	
	switch (this->status) {
	case ElevatorStatus::is_up:
		if (!this->isPlayerOn(player))
			return;
		this->status = ElevatorStatus::moving_down;
		break;
	case ElevatorStatus::is_down:
		if (!this->isPlayerOn(player))
			return;
		this->status = ElevatorStatus::moving_up;
		break;
	case ElevatorStatus::moving_up:
		for (int i = 0; i < this->speed; i++) {
			
			if (this->HasToStop()) {
				if (!this->isPlayerOn(player)) {
					this->status = ElevatorStatus::is_up;
					this->SwapLocations();
				}
			}
			else {
				if (this->isPlayerOn(player))
					player.MoveUp();
				this->MoveUp();
			}
				
		}
		break;
	case ElevatorStatus::moving_down:
		for (int i = 0; i < this->speed; i++) {
			if (this->HasToStop()) {
				if (!this->isPlayerOn(player)) {
					this->status = ElevatorStatus::is_down;
					this->SwapLocations();
					this->stop_location->AddToY(-16);
				}
					
			}
			else {
				if (this->isPlayerOn(player))
					player.MoveDown();
				this->MoveDown();
			}
		}
		break;
	default:
		assert(0);
	}

}

bool Elevator::isPlayerOn(Player& player) {
	int player_x = player.GetX();
	int player_y = player.GetY();
	int player_height = player.GetHeight();
	if (this->coordinates->GetX() <= player_x && player_x <= this->coordinates->GetX() + this->width && this->coordinates->GetY() - 24 <= player_y && player_y  <= this->coordinates->GetY()) {
		return true;
	}
	return false;
}

void Elevator::Render(double curr_time, int relative_x) {
	int x = this->coordinates->GetX() - relative_x;
	int y = this->coordinates->GetY();
	this->animator->render(x, y, curr_time, 0);
	//al_draw_rectangle(x , y, x + this->width, y + this->height, al_map_rgb(150, 0, 0), 0);
}