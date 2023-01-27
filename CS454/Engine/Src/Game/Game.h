#pragma once
#ifndef GAMEINCLUDE
#define GAMEINCLUDE

#include <iostream>
#include <functional>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "../Map/Map.h"
#include "../Misc/Timer/Timer.h"
#include "../Misc/Screen/Screen.h"
#include "../Player/Player.h"
#include "../Misc/MusicPlayer/MusicPlayer.h"
#include "../Utils/Point.h"
#include "../Utils/ExitPoint.h"
#include "../Utils/player_state.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;
//https://github.com/nlohmann/json#read-json-from-a-file
//gia to manual tu json

#define KEY_SEEN     1
#define KEY_RELEASED 2

enum class game_state {
	paused = 0,
	playing = 1
};

class Game { // app::Game namespace, the mother application
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;
	void Invoke(const Action& f) { if (f) f(); }

	//PLAYER
	Player* player1;
	

	//BUFFER
	ALLEGRO_BITMAP* buffer;
	int stats_display_height_offset;

	//MAP
	Map* background_map;

	//Ticker
	Timer* timer;

	//SCREEN
	Screen* screen;

	//LOOP FLAGS
	bool redraw = true;
	bool doneFlag = false;

	//EVENTS
	ALLEGRO_EVENT_QUEUE* queue; //event queue
	ALLEGRO_EVENT event; //event

	//input key capture
	unsigned char key[ALLEGRO_KEY_MAX];
	bool key_pressed;


	// Physics
	int jump_y;

	// Ai
	bool ai_flag = false;


	//MUSIC PLAYER
	MusicPlayer* music_player;

	//GAME STATE
	game_state game_state;
	
	//handles in game input
	void HandleInput();
	void HandlePauseInput();
	
	void PauseGame();
	void ResumeGame();
	void RenderPauseScreen();
public:
	//constructor
	Game();

	//initialise
	void Initialise(void);

	//config files
	void LoadSetting(void);

	//setters
	void SetRender(const Action& f) { render = f; }
	void SetAnim(const Action& f) { anim = f; }
	void SetInput(const Action& f) { input = f; }
	void SetAI(const Action& f) { ai = f; }
	void SetPhysics(const Action& f) { physics = f; }
	void SetDestruct(const Action& f) { destruct = f; }
	void SetCollisions(const Action& f) { collisions = f; }
	void SetUser(const Action& f) { user = f; }

	//REGISTER
	void Register();


	void ProgressAnimations(void) { Invoke(anim); }
	void Input(void) { Invoke(input); }
	void AI(void) { Invoke(ai); }
	void Physics(void) { Invoke(physics); }
	void CollisionChecking(void) { Invoke(collisions); }
	void CommitDestructions(void) { Invoke(destruct); }
	void UserCode(void) { Invoke(user); }
	bool IsFinished(void) const { return !done(); }
	
	void CheckExit();
	void ChangeMap(MapLocations new_map);
	void ChangeMap(std::string new_map, Point* spawn_location);

	//getters
	Map* GetMap(void) { return background_map; }
	Timer* GetTimer(void) { return timer; }

	//loops
	void MainLoop(void);
	void MainLoopIteration(void);

	//Renderers
	void Render(void);
	void StartRender(void);
	void DrawBufferToScreen(void);



	void HandlePhysics(void);
	void HandlePlayerPhysics(void);
	void HandleMapEnemiesPhysics(void);
	void HandleMapItemPhysics(void);
};
#endif