#include "Map.h"

Map::Map(std::string tilemapPath, int tilemapWidth , int tilemapHeight, const char* bitmapPath, int tilesetWidth, int tilesetHeight) {
	this->bitmap = new BitMap(bitmapPath, tilesetWidth, tilesetHeight);
	this->tilemap = new TileMap(tilemapWidth, tilemapHeight, tilemapPath);
	this->map_buffer = al_create_bitmap(MUL_16(tilemapWidth), MUL_16(tilemapHeight));
}

void Map::Render(int left_x, int max_x) {
	// left_x is the starting map point and it will render up to max_x
	// max_x - left_x == screen_width always!
	//std::cout << "x: " << left_x << std::endl << "max_x: " << max_x << std::endl << "mapWidth: " << MUL_16(this->tilemap->getTilemapWidth()) << std::endl;
	assert(left_x >= 0 && left_x <= max_x && max_x <= MUL_16(this->tilemap->getTilemapWidth()));
	al_lock_bitmap(this->map_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_hold_bitmap_drawing(true);

	al_draw_bitmap_region(this->map_buffer,
		0,								// sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
		0,								// sy -> 0 (logika, giati othoni.height = map.height)
		160,							// sw -> megethos othonis x 
		160,	// sh -> megethos othonis y
		0,								// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
		0,								// dy -> 0
		0);								// flags


	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(this->map_buffer);
}


void Map::BlitSelf(int x, int y, int scaling_factor, int screen_width, int screen_height) {
	//FIXME gia scaling factor = 1 vector skaei out of bounds 

	
	
	std::vector<std::vector<int>> tilemap = this->tilemap->getMap();

	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	
	int tile = 0;
	
	int max_height = this->tilemap->getTilemapHeight();
	int max_width = this->tilemap->getTilemapWidth();


	if (MUL_16(max_height) > screen_height) { //if tilemap * scale factor > screen height
		max_height = screen_height /MUL_16(scaling_factor) + 1;
	}

	if (MUL_16(max_width) > screen_width) { //if tilemap * scale factor > screen width
		max_width = screen_width / MUL_16(scaling_factor) + 1;
		
	}
	int tmp = this->tilemap->getTilemapWidth();
	if ((max_width + x) > tmp) {
		x = tmp - max_width;
	}
	
	tmp = this->tilemap->getTilemapHeight();

	
	if ((max_height + y) > tmp - 2) {
		printf("%d\n", max_height);
		y = tmp - max_height - 2;
	}
	
	int tilesetWidth = this->bitmap->getTilesetWidth();
	
	int size = tilemap.size();
	
	al_lock_bitmap(tileBitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	
	al_hold_bitmap_drawing(true);
	
	for (int height = 0; height < max_height ; height++) {
		for (int width = 0; width < max_width; width++) {
			tile = this->tilemap->getTile(x + width, y + height);
			
			/*al_draw_bitmap_region(
				tileBitmap,
				MUL_16((tile % tilesetWidth)) ,
				MUL_16((tile / tilesetWidth)) ,
				16,
				16,
				x + MUL_16(width),
				y + MUL_16(height),
				0);*/
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
	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(tileBitmap);
	
}


void Map::PrecomputeMap() { //TODO this parameter is probably useless

	int tile;
	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	int tilesetWidth = this->bitmap->getTilesetWidth();
	
	al_set_target_bitmap(this->map_buffer);
	al_lock_bitmap(tileBitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_lock_bitmap(this->map_buffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	al_hold_bitmap_drawing(true);
	
	for (int height = 0; height < this->tilemap->getTilemapHeight(); height++) {
		for (int width = 0; width < this->tilemap->getTilemapWidth(); width++) {
			tile = this->tilemap->getTile(width, height);
			std::cout << tile << ' ';
			al_draw_bitmap_region(tileBitmap,
				MUL_16((tile % tilesetWidth)),  // sx -> aristera tou paikth kai deksia tou paikth, k, l, tetoia wste k + l = screen width
				MUL_16((tile / tilesetWidth)),  // sy -> 0 (logika, giati othoni.height = map.height)
				16,							    // sw -> megethos othonis x 
				16,								// sh -> megethos othonis y
				(MUL_16(width)),				// dx -> 0 (.. h opou ksekinaei to panw aristera ths othonis, see alegro)
				(MUL_16(height)),				// dy -> 0
				0);								// flags
		}
		std::cout << std::endl;
	}
	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(tileBitmap);
	al_unlock_bitmap(this->map_buffer);
	//al_flip_display();
}

