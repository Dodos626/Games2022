#pragma once
#ifndef MAP_INCLUDE
#define MAP_INCLUDE
#include "../BitMap/BitMap.h"
#include "../Tiles/Map/TileMap.h"
#include "../Utils/Point.h"
#include "../Utils/ExitPoint.h"
#include "../Utils/MapEntities.h"
#include "../Entities/Items/item.h"
#include "../Entities/Enemies/Enemy.h"
#include <string>
#include <vector>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;
#define MUL_16(x) (x << 4)

enum class MapLocations {
	loading, // loading screen
	main_screen, //the main screen
	palace, // the first map
	first_floor, // the first floor
	first_floor_right // the first floor right
};


class Map {
private:
	BitMap *bitmap;   //png
	TileMap *tilemap; //csv
	TileMap *bgtilemap; //background csv
	ALLEGRO_BITMAP *map_buffer; // whole map buffer
	ALLEGRO_BITMAP *mapBG_buffer; //whole map bg buffer
	std::vector<int> SolidBlockIds;
	std::vector<ExitPoint> ExitPointBlocks;
	std::vector<std::vector<bool>> grid;
	std::vector<Entity*> entities;
	int player_dx;
	MapLocations state;
	Point *spawn;
	json data;

	//helpers to load the map
	void setSolidBlocks(std::vector<int> SolidBlockIds);
	void setTileMap(json data);
	void setSpawn(json data);
	void setExitPoints(json data);
	void setEntities(json data);
	std::string stateToString(MapLocations state);

	//gia to main screen ta grammata
	void mainScreenRender();

	void precomputeBg();

	void cleanBuffer(ALLEGRO_BITMAP* buffer);
public:
	Map(std::string Path);
	void PrecomputeMap();
	void Render(int left_x, int max_x, int y, int max_y);
	void RenderBg(int left_x, int max_x, int y, int max_y);
	BitMap* getBitMap() { return this->bitmap; };
	TileMap* getTileMap() { return this->tilemap; };
	ALLEGRO_BITMAP* getMapBuffer() { return this->map_buffer; };
	bool IsSolid(int x, int y);
	bool IsExit(Point location);
	ExitPoint GetExit(Point location);
	
	
	void setState(MapLocations state) { this->state = state; };
	MapLocations getState() { return this->state; }; 

	Point *GetSpawn() { return this->spawn; }

	void ChangeMap(MapLocations state) { this->ChangeMap(stateToString(state)); this->state = state; };
	void ChangeMap(std::string map);

};

#endif