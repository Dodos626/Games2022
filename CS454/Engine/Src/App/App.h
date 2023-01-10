#pragma once
#ifndef APPINCLUDE
#define APPINCLUDE
#define ALLEGRO_STATICLINK 1

#include <iostream>

#include "../Tiles/Parser/TileParser.h"
#include "../Game/Game.h"
#include "../BitMap/BitMap.h"
#include <stdio.h>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "../Misc/Screen/Screen.h"
#include "../Misc/Timer/Timer.h"


namespace app {
	class App {
	protected:
		Game game;
	public:
		App();
		virtual void Initialise(void) ; // Init Allegro, then Game
		virtual void Register(void) ; // Register Mouse/Keyboard based on config
		virtual void Load(void) ; // For now, wrapper of game load
		virtual void Run(void) { game.MainLoop(); } // Wrapper of game run
		virtual void Destroy(void) ; // Free memory
		virtual void RunIteration(void) // pass one iteration (?)
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
