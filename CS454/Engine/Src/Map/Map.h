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

	//collision detector helpers
	int x_bound, y_bound;
public:
	Map(std::string Path);
	~Map() {
		delete this->bitmap;
		delete this->tilemap;
		delete this->bgtilemap;
		for (int i = 0; i < this->entities.size(); i++)
			delete this->entities[i];
		delete this->spawn;
		al_destroy_bitmap(this->map_buffer);
		al_destroy_bitmap(this->mapBG_buffer);
	}
	void PrecomputeMap();
	void Render(int left_x, int max_x, int y, int max_y);
	void RenderBg(int left_x, int max_x, int y, int max_y);
	BitMap* getBitMap() { return this->bitmap; }
	TileMap* getTileMap() { return this->tilemap; }
	ALLEGRO_BITMAP* getMapBuffer() { return this->map_buffer; }
	std::vector<Entity*> GetMapEntities() { return this->entities; }
	bool IsSolid(int x, int y);
	bool IsExit(Point location);
	ExitPoint GetExit(Point location);
	Point* GetSpawn() { return this->spawn; }
	
	void setState(MapLocations state) { this->state = state; };
	MapLocations getState() { return this->state; }; 

	
	
	void RenderEntities(double curr_time, int relative_x);

	void ChangeMap(MapLocations state) { this->ChangeMap(stateToString(state)); this->state = state; };
	void ChangeMap(std::string map);


	void AiUpdate(Point player_position);

	//Collision Detector
	bool TryMoveDown(int x, int y, int width, int height);
	bool TryMoveUp(int x, int y, int width, int height);
	bool TryMoveLeft(int x, int y, int width, int height);
	bool TryMoveRight(int x, int y, int width, int height);

	//returns the X that is the offset of the camera relating to the map
	int GetCameraOffsetX(int camera_x, int camera_width) {
		int camera_stops_at = MUL_16(this->bgtilemap->getTilemapWidth());

		if (camera_x + camera_width > camera_stops_at) {
			camera_x = camera_stops_at - camera_width;
		}
		return camera_x;
	}

};

#endif