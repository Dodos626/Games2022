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

	
	
	
	this->map_buffer = al_create_bitmap(MUL_16(this->data["loading_screen"]["CSVwidth"]), MUL_16(this->data["loading_screen"]["CSVheight"]));
	this->mapBG_buffer = al_create_bitmap(MUL_16(this->data["loading_screen"]["background"]["CSVwidth"]), MUL_16(this->data["loading_screen"]["background"]["CSVheight"]));
	this->ChangeMap(this->state);
	
}

//change map

void Map::ChangeMap(MapLocations state) {
	//al_destroy_bitmap(this->map_buffer);
    //al_destroy_bitmap(this->mapBG_buffer);

	//this->map_buffer = al_create_bitmap(MUL_16(this->data[this->stateToString(state)]["CSVwidth"]), MUL_16(this->data[this->stateToString(state)]["CSVheight"]));
	//this->mapBG_buffer = al_create_bitmap(MUL_16(this->data[this->stateToString(state)]["background"]["CSVwidth"]), MUL_16(this->data[this->stateToString(state)]["background"]["CSVheight"]));
	
	std::string map = stateToString(state);
	this->cleanBuffer(this->map_buffer);
	this->cleanBuffer(this->mapBG_buffer);
	this->setTileMap(this->data[map]);
	this->setSolidBlocks(this->data[map]["SolidIds"]);
	this->setExitPoints(this->data[map]["exit_points"]);
	this->grid.clear();
	this->setSpawn(this->data[map]);
	this->state = state;
	this->precomputeBg();
	this->PrecomputeMap();
	
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
	case MapLocations::loading:
		return "loading_screen";
	case MapLocations::main_screen:
		return "main_screen";
	case MapLocations::palace:
		return "palace";
	case MapLocations::first_floor:
		return "first_floor";
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

void Map::setExitPoints(json data) {
	this->ExitPointBlocks.clear();
	for (auto pair : data.items()){
		std::string map_name = pair.key();
		auto points = pair.value();
		for (auto point : points) {
			this->ExitPointBlocks.push_back(Point(point["x"], point["y"], map_name));
		}
	}
}

