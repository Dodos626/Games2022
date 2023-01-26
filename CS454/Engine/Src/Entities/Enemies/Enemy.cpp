#include "Enemy.h"
#include "../../Utils/MapEntities.h"

using json = nlohmann::json;

Enemy::Enemy(Point *spawn, std::string datapath) {
	std::ifstream fin(datapath);
	json data = json::parse(fin);
	std::cout << data << std::endl;
	this->health = data["hp"];
	this->damage = data["ad"];
	this->speed = data["speed"];
	this->points = data["rp"];
	this->coordinates = spawn;
	this->animator = NULL;

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

void Enemy::GetDamaged(int damage) {
	if (!this->is_alive)
		return;
	this->health -= damage;
	// Animate Damage
	if (this->health <= 0)
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
}

void Enemy::Collide(Player& player) {
	player.TakeDamage(this->damage);
}