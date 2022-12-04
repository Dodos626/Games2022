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
#include "../Screen/Screen.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2


class Game { // app::Game namespace, the mother application
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;
	void Invoke(const Action& f) { if (f) f(); }
	
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
	
	void Render(void) { Invoke(render); }
	void ProgressAnimations(void) { Invoke(anim); }
	void Input(void) { Invoke(input); }
	void AI(void) { Invoke(ai); }
	void Physics(void) { Invoke(physics); }
	void CollisionChecking(void) { Invoke(collisions); }
	void CommitDestructions(void) { Invoke(destruct); }
	void UserCode(void) { Invoke(user); }
	bool IsFinished(void) const { return !done(); }

	//getters
	Map* GetMap(void) { return background_map; }
	Timer* GetTimer(void) { return timer; }

	//loops
	void MainLoop(void);
	void MainLoopIteration(void);
};

#endif