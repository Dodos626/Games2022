#pragma once
#ifndef TileParser
#define TileParser

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


/*Throw exception if file not found*/
std::vector<std::vector<int>> ReadTextMap(std::string filename,int width, int height);

void PrintTileMap(std::vector<std::vector<int>> tileMap, int width, int height);

#endif