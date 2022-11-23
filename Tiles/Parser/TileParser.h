#ifndef TileParser
#define TileParser

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



int ReadTextMap(std::string filename);
void PrintTileMap(std::vector<std::vector<int>> tileMap);

#endif