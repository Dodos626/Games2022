#include "Map.h"


Map::Map(std::string path) {

	std::ifstream f(path);
	this->data = json::parse(f);
	std::cout << this->data << std::endl;

	this->state = MapLocations::main_screen;
	
	//the bitmap is the same for all the maps
	std::string bitmapPath = this->data["png"]["PNGsource"].get<std::string>();
	int tilesetWidth = this->data["png"]["PNGwidth"];
	int tilesetHeight = this->data["png"]["PNGheight"];
	this->bitmap = new BitMap(bitmapPath.c_str(), tilesetWidth, tilesetHeight);
	this->spawn = new Point(0, 0);
	this->player_dx = MUL_16(2);
	
	
	//starting the maps

	
	
	//al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->map_buffer = al_create_bitmap(MUL_16(this->data["main_screen"]["CSVwidth"]), MUL_16(this->data["main_screen"]["CSVheight"]));
	this->mapBG_buffer = al_create_bitmap(MUL_16(this->data["main_screen"]["background"]["CSVwidth"]), MUL_16(this->data["main_screen"]["background"]["CSVheight"]));
	this->ChangeMap(this->state);
	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	this->y_bound = MUL_16(this->getTileMap()->getTilemapHeight());
	this->x_bound = MUL_16(this->getTileMap()->getTilemapWidth());
}


void Map::ChangeMap(std::string map) {
	//al_destroy_bitmap(this->map_buffer);
    //al_destroy_bitmap(this->mapBG_buffer);

	//this->map_buffer = al_create_bitmap(MUL_16(this->data[this->stateToString(state)]["CSVwidth"]), MUL_16(this->data[this->stateToString(state)]["CSVheight"]));
	//this->mapBG_buffer = al_create_bitmap(MUL_16(this->data[this->stateToString(state)]["background"]["CSVwidth"]), MUL_16(this->data[this->stateToString(state)]["background"]["CSVheight"]));
	
	this->cleanBuffer(this->map_buffer);
	this->cleanBuffer(this->mapBG_buffer);
	this->setTileMap(this->data[map]);
	this->setSolidBlocks(this->data[map]["SolidIds"]);
	this->setExitPoints(this->data[map]["exit_points"]);
	this->setEntities(this->data[map]["entities"]);
	this->grid.clear();
	this->setSpawn(this->data[map]);
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	this->precomputeBg();
	this->PrecomputeMap();
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	
}

void Map::cleanBuffer(ALLEGRO_BITMAP* buffer) { //TODO veltiwsh epidoshs

	al_set_target_bitmap(buffer);

	//al_lock_bitmap(buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	//al_hold_bitmap_drawing(true);
	
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(buffer, al_map_rgb(0, 0, 0));
	
	//al_hold_bitmap_drawing(false);
	//al_unlock_bitmap(buffer);
}


//HELPERS  TO LOAD OTHER MAPS
std::string Map::stateToString(MapLocations state) {
	switch (state)
	{
	case MapLocations::win_screen:
		return "win_screen";
	case MapLocations::main_screen:
		return "main_screen";
	case MapLocations::palace:
		return "palace";
	case MapLocations::first_floor:
		return "first_floor";
	case MapLocations::first_floor_right:
		return "first_floor_right";
	case MapLocations::loose_screen:
		return "loose_screen";
	default:
		exit(EXIT_FAILURE);
	}
}

void Map::setSolidBlocks(std::vector<int> SolidBlockIds) {
	this->SolidBlockIds = SolidBlockIds;
}

void Map::setTileMap(json data) {
	if (this->tilemap != nullptr)
		delete this->tilemap;
	this->tilemap = new TileMap(data["CSVwidth"], data["CSVheight"], data["CSVsource"]);
	
	if (this->bgtilemap != nullptr)
		delete this->bgtilemap;
	this->bgtilemap = new TileMap(data["background"]["CSVwidth"], data["background"]["CSVheight"], data["background"]["CSVsource"]);
}

void Map::setSpawn(json data) {
	this->spawn->SetX(data["spawn_x"]);
	this->spawn->SetY(data["spawn_y"]);
}

void Map::Render(int left_x, int max_x, int y, int max_y) {
	// left_x is the starting map point and it will render up to max_x
	// max_x  == screen_width always!
	
	//assert(left_x >= 0 && left_x <= max_x && max_x - left_x <= MUL_16(this->tilemap->getTilemapWidth()));
	
	
	if (left_x + max_x > MUL_16(this->tilemap->getTilemapWidth())) { //tsekarei na min bgei to x pio deksia apo oti prepei
		left_x = MUL_16(this->tilemap->getTilemapWidth()) - max_x;
		max_x = MUL_16(this->tilemap->getTilemapWidth());
		
	}

	
	al_lock_bitmap(this->map_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_hold_bitmap_drawing(true);
	
	al_draw_bitmap_region(this->map_buffer,
		left_x,					// sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
		y,								// sy -> 0 (logika, giati othoni.height = map.height)
		max_x,					// sw -> megethos othonis x 
		max_y,							// sh -> megethos othonis y
		0,								// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
		0,								// dy -> 0
		0);								// flags

	
		
	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(this->map_buffer);
}
void Map::RenderBg(int left_x, int max_x, int y, int max_y) {
	
	
	
	
	if (left_x + max_x > MUL_16(this->bgtilemap->getTilemapWidth())) { //tsekarei na min bgei to x pio deksia apo oti prepei
		left_x = MUL_16(this->bgtilemap->getTilemapWidth()) - max_x;
		max_x = MUL_16(this->bgtilemap->getTilemapWidth());
	}

	al_lock_bitmap(this->mapBG_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_hold_bitmap_drawing(true);

	al_draw_bitmap_region(this->mapBG_buffer,
		left_x/2,					// sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
		y,								// sy -> 0 (logika, giati othoni.height = map.height)
		max_x,					// sw -> megethos othonis x 
		max_y,							// sh -> megethos othonis y
		0,								// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
		0,								// dy -> 0
		0);								// flags


	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(this->mapBG_buffer);
}

void Map::PrecomputeMap() { 

	
	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	int tilesetWidth = this->bitmap->getTilesetWidth();
	
	al_set_target_bitmap(this->map_buffer);
	
	al_lock_bitmap(tileBitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_lock_bitmap(this->map_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	al_hold_bitmap_drawing(true);
	
	
	for (int height = 0; height < this->tilemap->getTilemapHeight(); height++) {
		std::vector<bool> sub_grid;
		
		for (int width = 0; width < this->tilemap->getTilemapWidth(); width++) {
			
			const int tile = this->tilemap->getTile(width, height);
			sub_grid.push_back(std::find(this->SolidBlockIds.begin(), this->SolidBlockIds.end(), tile) != this->SolidBlockIds.end());
			
			
			
			
			al_draw_bitmap_region(tileBitmap,
				MUL_16((tile % tilesetWidth)),  // sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
				MUL_16((tile / tilesetWidth)),  // sy -> 0 (logika, giati othoni.height = map.height)
				16,							    // sw -> megethos othonis x 
				16,								// sh -> megethos othonis y
				(MUL_16(width)),				// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
				(MUL_16(height)),				// dy -> 0
				0);								// flags
			
		}
		
		this->grid.push_back(sub_grid);
	}
	
	
	al_unlock_bitmap(tileBitmap);
	al_unlock_bitmap(this->map_buffer);
	al_hold_bitmap_drawing(false);
	
	if (this->getState() == MapLocations::main_screen) {
		mainScreenRender();
	}
	
	
	
}
void Map::precomputeBg() {
	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	int tilesetWidth = this->bitmap->getTilesetWidth();

	al_set_target_bitmap(this->mapBG_buffer);
	
	al_lock_bitmap(tileBitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_lock_bitmap(this->mapBG_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	al_hold_bitmap_drawing(true);

	for (int height = 0; height < this->bgtilemap->getTilemapHeight(); height++) {

		for (int width = 0; width < this->bgtilemap->getTilemapWidth(); width++) {

			const int tile = this->bgtilemap->getTile(width, height);

			al_draw_bitmap_region(tileBitmap,
				MUL_16((tile % tilesetWidth)),  // sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
				MUL_16((tile / tilesetWidth)),  // sy -> 0 (logika, giati othoni.height = map.height)
				16,							    // sw -> megethos othonis x 
				16,								// sh -> megethos othonis y
				(MUL_16(width)),				// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
				(MUL_16(height)),				// dy -> 0
				0);								// flags
		}
	}

	al_unlock_bitmap(tileBitmap);
	al_unlock_bitmap(this->mapBG_buffer);
	al_hold_bitmap_drawing(false);

}

void Map::mainScreenRender() {
	//al_lock_bitmap(this->map_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	//al_hold_bitmap_drawing(true);
	
	ALLEGRO_FONT* font = al_create_builtin_font();
	const char* msg = "Press Enter to Start\n A game by Theodoros Chalkidis,\n George Manos and Minos\n UNIVERSITY OF CRETE\n COMPUTER SCIENCE DEPARTMENT\n CS454\n 2022-2023";
	al_draw_filled_rectangle(16, 16, 288, 104, al_map_rgb(255, 32, 65));
	al_draw_multiline_text(font, al_map_rgb(255, 255, 255), 150, 25, 288, 10, ALLEGRO_ALIGN_CENTRE, msg);
	al_destroy_font(font);
	//al_hold_bitmap_drawing(false);
	//al_unlock_bitmap(this->map_buffer);
	
}

bool Map::IsSolid(int x, int y) {
	return this->grid[y][x];
}

bool Map::IsExit(Point location) {
	return std::find(this->ExitPointBlocks.begin(), this->ExitPointBlocks.end(), location) != this->ExitPointBlocks.end();
}

ExitPoint Map::GetExit(Point location) {
	std::vector<ExitPoint>::iterator it = std::find(this->ExitPointBlocks.begin(), this->ExitPointBlocks.end(), location);
	if (it == this->ExitPointBlocks.end())
		assert(0);
	return this->ExitPointBlocks[it - this->ExitPointBlocks.begin()];
}

void Map::setExitPoints(json data) {
	this->ExitPointBlocks.clear();
	for (auto pair : data.items()){
		std::string map_name = pair.key();
		auto points = pair.value();
		for (auto point : points) {
			this->ExitPointBlocks.push_back(ExitPoint(point["x"], point["y"], map_name, new Point(point["spawn_x"], point["spawn_y"])));
		}
	}
}
void Map::setEntities(json data) {
	this->enemies.clear();
	for (auto enemy_pair : data["enemies"].items()) {
		std::string enemy_name = enemy_pair.key();
		for (auto spawn_location : enemy_pair.value()) {
			this->enemies.push_back(
				MapEntities::GetEnemyFromString(
					enemy_name,
					new Point(spawn_location["spawn_x"], spawn_location["spawn_y"]),
						std::bind(&Map::TryMoveLeft, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
						std::bind(&Map::TryMoveRight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
						std::bind(&Map::TryMoveUp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
						std::bind(&Map::TryMoveDown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
					));
		}
	}
	this->items.clear();
	for (auto item_pair : data["items"].items()) {
		std::string item_name = item_pair.key();
		for (auto spawn_location : item_pair.value()) {
			Point* spawn = new Point(spawn_location["spawn_x"], spawn_location["spawn_y"]);
			Item* item = MapEntities::GetItemFromString(item_name, spawn);
			if (item_name == "Door") {
				this->RegisterDoor((DoorItem *)item);
			}
			this->items.push_back(item);
		}
	}
	this->objects.clear();
	for (auto object_pair : data["objects"].items()) {
		std::string item_name = object_pair.key();
		for (auto spawn_location : object_pair.value()) {
			this->objects.push_back(new Elevator(new Point(spawn_location["spawn_x"], spawn_location["spawn_y"]), new Point(spawn_location["end_x"], spawn_location["end_y"]), MapEntities::GetElevatorStatusFromString(spawn_location["status"])));
		}
	}
}

void Map::RenderEntities(double curr_time, int relative_x) {
	this->RenderEnemies(curr_time, relative_x);
	this->RenderItems(curr_time, relative_x);
	this->RenderObjects(curr_time, relative_x);
}

void Map::RenderEnemies(double curr_time, int relative_x) {
	for (auto entity : this->enemies) {
		entity->Render(curr_time,relative_x);
	}
}

void Map::RenderItems(double curr_time, int relative_x) {
	for (auto entity : this->items) {
		entity->Render(curr_time, relative_x);
	}
}

void Map::RenderObjects(double curr_time, int relative_x) {
	for (auto entity : this->objects) {
		entity->Render(curr_time, relative_x);
	}
}


void Map::AiUpdate(Player *player) {
	for (auto entity : this->enemies) {
		entity->AI(*player);
	}
	for (auto object : this->objects) {
		object->AI(*player);
	}
}


//COLLISION DETECTORS
bool Map::CheckObjectCollision(Player &player) {
	for (Elevator* elevator : this->objects) {
		if (elevator->isPlayerOn(player))
			return true;
	}
	return false;
}


bool Map::TryMoveDown(int x, int y, int width, int height) {
	if (y + height >= this->y_bound)
		return false;
	int lx = x / 16;									// left x
	int dy = (y + height) / 16;		// left down y + height (tiles)
	int rx = (x + width - 1) / 16;								// right x
	return !(this->IsSolid(lx, dy) || this->IsSolid(rx, dy));
}

bool Map::PlayerMoveDown(Player& player) {
	int x = player.GetX();
	int y = player.GetY();
	int width = player.GetWidth();
	int height = player.GetHeight();
	return (this->TryMoveDown(x, y, width, height) && !this->CheckObjectCollision(player));

}

bool Map::TryMoveUp(int x, int y, int width, int height) {
	if (y <= 0)
		return false;
	int lx = x / 16;			// left x
	int uy = (y - 1) / 16;		// left upper y - 1
	int rx = (x + width - 1) / 16;		// right x
	return !(this->IsSolid(lx, uy) || this->IsSolid(rx, uy));
}

bool Map::TryMoveLeft(int x, int y, int width, int height) {
	if (x <= 0)
		return false;
	int lx = (x - 1) / 16;		// left x - 1
	int uy = (y) / 16;			// upper y
	int my = (y + (height / 2) - 1) / 16;		// middle y
	int dy = (y + height - 1) / 16;		// down y

	return !(this->IsSolid(lx, uy) || this->IsSolid(lx, my) || this->IsSolid(lx, dy));
}

bool Map::TryMoveRight(int x, int y, int width, int height) {
	if (x + width >= this->x_bound)
		return false;
	int rx = (x + width) / 16;		// right x + 1
	int uy = (y) / 16;			// upper y
	int my = (y + (height / 2) - 1) / 16;		// middle y
	int dy = (y + height - 1) / 16;		// down y

	return !(this->IsSolid(rx, uy) || this->IsSolid(rx, my) || this->IsSolid(rx, dy));

}

bool Map::TryAttack(int x, int y) {
	if (x  < 0 || x  >= this->x_bound || y  < 0 || y  >= this->y_bound)
		return false;
	return !(this->IsSolid(x/16, y/16) );
}

void Map::KillAllEnemies(Player *player) {
	// The final solution
	for (Enemy* enemy : this->enemies) {
		enemy->KillInstantly();
		player->IncreasePoints(enemy->GetPoints());
		Item* drop = enemy->GetDroppedItem();
		if (drop)
			this->items.push_back(drop);
	}
	this->enemies.clear();
}


void Map::PlayerAttack(Player *player) {
	Point coordinates = player->GetAttackPoint();
	int damage = player->GetAttackPower();
	for (int i = 0; i < this->enemies.size(); i++) {
		Enemy* enemy = this->enemies[i];
		if (enemy->GetX() <= coordinates.GetX() && coordinates.GetX() <= enemy->GetX() + enemy->GetWidth() &&
			enemy->GetY() <= coordinates.GetY() && coordinates.GetY() <= enemy->GetY() + enemy->GetHeight()) {
			int tmp = 0;
			if (player->isDucking()) {
				tmp += 16;
			}
			enemy->GetAttacked(damage, Point(player->GetX(), player->GetY() + tmp));
			std::cout << "attacking enemy " << *enemy << std::endl;
			if (!enemy->GetIsAlive()) {
				player->IncreasePoints(enemy->GetPoints());
				Item* drop = enemy->GetDroppedItem();

				if (drop)
					this->items.push_back(drop);

				this->enemies.erase(this->enemies.begin() + i);
				return;
			}
		}
			
			
	}

}
void Map::CheckPlayerCollisionsWithEntities(Player *player) {
	int pl_ux = player->GetX();
	int pl_ly = player->GetY();
	int pl_width = player->GetWidth();
	int pl_height = player->GetHeight();
	Point  p(pl_ux, pl_ly);
	for (Enemy* enemy : this->enemies) {
		int en_ux = enemy->GetX();
		int en_ly = enemy->GetY();
		int en_width = enemy->GetWidth();
		int en_height = enemy->GetHeight();
		Point ul(en_ux, en_ly);
		Point dl(en_ux, en_ly + en_height);
		Point ur(en_ux + en_width, en_ly);
		Point dr(en_ux + en_width, en_ly + en_height);
		if (p.InRectangle(ul, pl_width, pl_height) || p.InRectangle(dl, pl_width, pl_height) || p.InRectangle(ur, pl_width, pl_height) || p.InRectangle(dr, pl_width, pl_height)) {
			enemy->Collide(*player);
			return;
		}
	}
	for (int i = 0; i < this->items.size(); i++) {
		Item* item = this->items[i];
		int en_ux = item->GetX();
		int en_ly = item->GetY();
		int en_width = item->GetWidth();
		int en_height = item->GetHeight();
		Point ul(en_ux, en_ly);
		Point dl(en_ux, en_ly + en_height);
		Point ur(en_ux + en_width, en_ly);
		Point dr(en_ux + en_width, en_ly + en_height);
		if (p.InRectangle(ul, pl_width, pl_height) || p.InRectangle(dl, pl_width, pl_height) || p.InRectangle(ur, pl_width, pl_height) || p.InRectangle(dr, pl_width, pl_height)) {
			item->PickUp(*player);
			if (item->GetName() == "Door") {
				if (!((DoorItem*)item)->GetIsLocked()) {
					this->RemoveDoor((DoorItem*)item);
					this->items.erase(this->items.begin() + i);
				}
			} else
				this->items.erase(this->items.begin() + i);
			return;
		}
	}
}

void Map::RegisterDoor(DoorItem* door) {
	int dx = door->GetX();
	int dy = door->GetY();
	int height = door->GetHeight();
	int b1x = (dx) / 16;
	int b1y = (dy) / 16;
	int b2y = b1y + 1;
	int b3y = b2y + 1;
	std::cout << "registering door at:" << b1x << " , y = " << b1y << std::endl;
	std::cout << "Grid before changes:\n";
	for (int i = 0; i < this->grid.size(); i++) {
		for (int j = 0; j < this->grid[i].size(); j++) {
			std::cout << this->grid[i][j];
		}
		std::cout << std::endl;
	}
	this->grid[b1y][b1x] = true;
	this->grid[b2y][b1x] = true;
	this->grid[b3y][b1x] = true;

	std::cout << "\n\nGrid after changes:\n";
	for (int i = 0; i < this->grid.size(); i++) {
		for (int j = 0; j < this->grid[i].size(); j++) {
			std::cout << this->grid[i][j];
		}
		std::cout << std::endl;
	}
}

void Map::RemoveDoor(DoorItem* door) {
	int dx = door->GetX();
	int dy = door->GetY();
	int height = door->GetHeight();
	int b1x = (dx) / 16;
	int b1y = (dy) / 16;
	int b2y = b1y + 1;
	int b3y = b2y + 1;
	std::cout << "removing door at:" << b1x << " , y = " << b1y << std::endl;
	this->grid[b1y][b1x] = false;
	this->grid[b2y][b1x] = false;
	this->grid[b3y][b1x] = false;

}