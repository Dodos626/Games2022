#include "Map.h"

Map::Map(std::string tilemapPath, int tilemapWidth , int tilemapHeight, const char* bitmapPath, int tilesetWidth, int tilesetHeight) {
	this->bitmap = new BitMap(bitmapPath, tilesetWidth, tilesetHeight);
	this->tilemap = new TileMap(tilemapWidth, tilemapHeight, tilemapPath);
}

void Map::BlitSelf(int x, int y, int scaling_factor, int screen_width, int screen_height) {
	//FIXME gia scaling factor = 1 vector skaei out of bounds 

	
	
	std::vector<std::vector<int>> tilemap = this->tilemap->getMap();

	ALLEGRO_BITMAP* tileBitmap = this->bitmap->getBitMap();
	
	int tile = 0;
	
	int max_height = this->tilemap->getTilemapHeight();
	int max_width = this->tilemap->getTilemapWidth();


	if (MUL_16(max_height)*scaling_factor > screen_height) { //if tilemap * scale factor > screen height
		max_height = screen_height /MUL_16(scaling_factor) + 1;
	}

	if (MUL_16(max_width)* scaling_factor > screen_width) { //if tilemap * scale factor > screen width
		max_width = screen_width / MUL_16(scaling_factor) + 1;
		
	}
	int tmp = this->tilemap->getTilemapWidth();
	if ((max_width + x) > tmp) {
		x = tmp - max_width;
	}
	
	tmp = this->tilemap->getTilemapHeight();

	
	if ((max_height + y) > tmp - 2) {
		
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
			
			al_draw_tinted_scaled_rotated_bitmap_region(
				tileBitmap,
				MUL_16((tile % tilesetWidth)),
				MUL_16((tile / tilesetWidth)),
				16,
				16,
				al_map_rgb(255, 255, 255), // color, just use white if you don't want a tint
				0, 0,					// center of rotation/scaling
				(MUL_16(width)*scaling_factor),
				(MUL_16(height)* scaling_factor),  // destination
				scaling_factor, scaling_factor,      // scale
				0, 0);  // angle and flags
			
		}
	}
	al_hold_bitmap_drawing(false);
	al_unlock_bitmap(tileBitmap);
	
	
	

	
	
}


