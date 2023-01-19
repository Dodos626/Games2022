#pragma once
#ifndef MAP_INCLUDE
#define MAP_INCLUDE
#include "../BitMap/BitMap.h"
#include "../Tiles/Map/TileMap.h"
#include <string>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;
#define MUL_16(x) (x << 4)

enum class map_state {
	loading, // loading screen
	main_screen, //the main screen
	playing, // the first map
	first_floor // the first floor
};

struct Spawn{
	int x;
	int y;
};


class Map {
private:
	BitMap *bitmap;   //png
	TileMap *tilemap; //csv
	ALLEGRO_BITMAP *map_buffer; // whole map buffer
	std::vector<int> SolidBlockIds;
	std::vector<std::vector<bool>> grid;
	int player_dx;
	map_state state;
	Spawn spawn;
	json data;

	//helpers to load the map
	void setSolidBlocks(std::vector<int> SolidBlockIds);
	void setTileMap(json data);
	void setSpawn(json data);
	std::string stateToString(map_state state);
public:
	Map(std::string Path);
	void PrecomputeMap();
	void Render(int left_x, int max_x, int y, int max_y);
	BitMap* getBitMap() { return this->bitmap; };
	TileMap* getTileMap() { return this->tilemap; };
	ALLEGRO_BITMAP* getMapBuffer() { return this->map_buffer; };
	bool IsSolid(int x, int y);
	
	
	void setState(map_state state) { this->state = state; };
	map_state getState() { return this->state; }; 

	Spawn getSpawn() { return this->spawn; };

	void ChangeMap(map_state state);

};

#endif