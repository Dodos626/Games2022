#pragma once
#ifndef APPINCLUDE
#define APPINCLUDE
#define ALLEGRO_STATICLINK 1

#include <iostream>

#include "../Tiles/Parser/TileParser.h"
#include "../../UnitTests/UnitTest1Media/UnitTest1.h"
#include "../Game/Game.h"
#include "../BitMap/BitMap.h"
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>


namespace app {
	class App {
	protected:
		Game game;
	public:
		virtual void Initialise(void) = 0;
		virtual void Load(void) = 0;
		virtual void Run(void) { game.MainLoop(); }
		virtual void RunIteration(void)
		{
			game.MainLoopIteration();
		}
		Game& GetGame(void) { return game; }
		const Game& GetGame(void) const { return game; }
		virtual void Clear(void) = 0;
		void Main(void) {
			Initialise();
			Load();
			Run();
			Clear();
		}
	};
}


#endif 
