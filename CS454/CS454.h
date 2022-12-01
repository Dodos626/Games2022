#pragma once
#ifndef MAINFILEINCLUDE
#define MAINFILEINCLUDE

#define ALLEGRO_STATICLINK 1

#include <iostream>

#include "Engine/Src/Tiles/Parser/TileParser.h"
#include "UnitTests/UnitTest1Media/UnitTest1.h"
#include "Engine/Src/BitMap/BitMap.h"
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "Engine/Src/Map/Map.h"


#define SCREEN_W 800
#define SCREEN_H 600

int init_all();


double fps(double old_time);
double avg_fps = 0;
double fps_timer = 0;
double delta = 0;

#endif // !MAINFILEINCLUDE

