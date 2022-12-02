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
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "../Screen/Screen.h"
#include "../Misc/Timer/Timer.h"


namespace app {
	class App {
	protected:
		Game game;
	public:
		App();
		virtual void Initialise(void) ; // init 
		virtual void Register(void) ; //to register
		virtual void Load(void) ; // load components and stuff
		virtual void Run(void) { game.MainLoop(); } // start the game
		virtual void Destroy(void) ; // destroy components and stuff
		virtual void RunIteration(void) // pass one iteration
		{
			game.MainLoopIteration();
		}
		Game& GetGame(void) { return game; }
		const Game& GetGame(void) const { return game; }
		virtual void Clear(void) { ; };
		void Main(void) {
			Initialise();
			Register();
			Load();
			Run();
			Clear();
		}

	};
}


#endif 
