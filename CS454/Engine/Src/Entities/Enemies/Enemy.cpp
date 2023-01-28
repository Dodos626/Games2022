#include "Enemy.h"
#include "../../Utils/MapEntities.h"
#include <assert.h>

using json = nlohmann::json;

Enemy::Enemy(Point *spawn, std::string datapath, Action tryMoveLeft_, Action tryMoveRight_, Action tryMoveUp_, Action tryMoveDown_):
	tryMoveLeft(tryMoveLeft_),
	tryMoveRight(tryMoveRight_),
	tryMoveUp(tryMoveUp_),
	tryMoveDown(tryMoveDown_)
{
	std::ifstream fin(datapath);
	json data = json::parse(fin);
	std::cout << data << std::endl;
	this->health = data["hp"];
	this->damage = data["ad"];
	this->speed = data["speed"];
	this->points = data["rp"];
	this->coordinates = spawn;
	this->animator = NULL;
	this->view_distance = data["view_distance"];
	this->percentage = 100;
	this->dropped_item = NULL;
	this->is_alive = true;

	this->width = data["width"];
	this->height = data["height"];
	srand(time(NULL));

	this->drop_chance = data["drop_chance"];
	for (auto item : data["drops"])
		this->drops.push_back(MapEntities::GetItemFromString(item, this->coordinates));
}

void Enemy::GetAttacked(int damage, Point point_of_attack) {
	if (!this->is_alive )
		return;
	this->health -= damage;
	this->takes_damage = true;
	// Animate Damage
	if (this->health <= 0)
		this->_Death();
}

void Enemy::KillInstantly(void) {
	this->health = 0;
	this->_Death();
}


void Enemy::_Death() {
	this->is_alive = false;
	// Animate death
	int roll = rand() % this->percentage;
	if (roll <= this->drop_chance)
		this->_DropItem();
	
}

void Enemy::_DropItem() {
	this->dropped_item = this->drops[rand() % this->drops.size()];
	assert(*this->dropped_item->GetCoordinates() == *this->coordinates);
}

void Enemy::Collide(Player& player) {
	player.TakeDamage(this->damage, Point(this->GetX(), this->GetY()));
	this->ChangeDirection();
}