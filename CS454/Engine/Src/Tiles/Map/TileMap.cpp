#include "TileMap.h"

#define MAX_WIDTH 1024
#define MAX_HEIGHT 256
typedef unsigned short Dim;
//typedef Index TileMap[MAX_WIDTH][MAX_HEIGHT];
		
int TileMap::setMap(std::string path) {
	try {
		this->map = ReadTextMap(path, this->width, this->height);
		return 1;
	}
	catch (std::string Exception){
		std::cout << Exception << "\n";
		return -1;
	}
	return 1;
}

TileMap::TileMap(int width, int height, std::string path) {
	this->width = width;
	this->height = height;
	this->setMap(path);
}
void TileMap::PrintSelf() {
	if (this->map.size() == 0) {
		std::cout << "This map is empty";
		return;
	}
	PrintTileMap(this->map, this->width, this->height);
}
		
