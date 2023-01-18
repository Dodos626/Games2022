#include "Map.h"

Map::Map(std::string tilemapPath, int tilemapWidth , int tilemapHeight, const char* bitmapPath, int tilesetWidth, int tilesetHeight, std::vector<int> SolidBlockIds) {
	this->bitmap = new BitMap(bitmapPath, tilesetWidth, tilesetHeight);
	this->tilemap = new TileMap(tilemapWidth, tilemapHeight, tilemapPath);
	this->map_buffer = al_create_bitmap(MUL_16(tilemapWidth), MUL_16(tilemapHeight));
	this->SolidBlockIds = SolidBlockIds;
	this->player_dx = MUL_16(2);
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


void Map::PrecomputeMap() { 

	
	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	int tilesetWidth = this->bitmap->getTilesetWidth();
	
	al_set_target_bitmap(this->map_buffer);
	al_clear_to_color(al_map_rgb(255, 255, 255));
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
	
	
}

bool Map::IsSolid(int x, int y) {
	return this->grid[y][x];
}
