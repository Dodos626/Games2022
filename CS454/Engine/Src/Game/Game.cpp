#include "Game.h"

Game::Game() {
	

	try {
		Initialise();
		
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		throw("terminating error in game\n");
	}
	this->music_player->Play(0); // plays the first song
	this->game_state = game_state::playing;
	MainLoop();
	
}

void Game::Initialise(void) {
	assert(al_init());
	assert(al_init_image_addon());
	assert(al_init_primitives_addon());

	//audio stuff
	assert(al_install_audio());
	assert(al_init_acodec_addon());
	al_reserve_samples(10);

	std::ifstream f("Engine/Configs/GameConfig.json");
	json data = json::parse(f);
	std::cout << data << std::endl;
	

	this->stats_display_height_offset = data["stats_display"]["height"]; // how much will displaying stats take of off screen
	
	this->timer = new Timer(data["ticker"]["rate"]); 
	this->timer->setPrintFPS(data["ticker"]["showfps"]); 
	this->screen = new Screen(data["screen"]["width"], data["screen"]["height"] + this->stats_display_height_offset, data["screen"]["scale"]);
	

	this->queue = al_create_event_queue();
	Register();
	
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP); // faster bitmaps display must be initialised
	
	this->buffer = al_create_bitmap(data["screen"]["width"] / 2, (data["screen"]["height"] - this->stats_display_height_offset) / 2);
	Point* spawn_location;
	std::cout << "creating map\n";
	try {
		auto background_json = data["bitmaps"]["background"];
		this->background_map = new Map("Engine/Configs/MapConfig.json");
		spawn_location = this->background_map->GetSpawn();
	}
	catch (std::string e) {
		throw( "Init of game failed, abort!\n");
		
	}
	memset(this->key, 0, sizeof(this->key)); // initiate input key buffer
	
	this->player1 = new Player(	spawn_location,
								this->screen->GetScaledWidth(),
								MUL_16(this->background_map->getTileMap()->getTilemapWidth()),
								data["screen"]["relative_location"],
								this->stats_display_height_offset,
								MUL_16(this->background_map->getTileMap()->getTilemapHeight())
							   );

	this->music_player = new MusicPlayer();
	
	
	
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	
	this->y_bound = MUL_16(this->background_map->getTileMap()->getTilemapHeight());
	this->x_bound = MUL_16(this->background_map->getTileMap()->getTilemapWidth());
	this->jump_y = 0;
	
	Action handle_input = [this]() {this->HandleInput(); };
	Action gravity_pull = [this]() {this->GravityPull(); };
	Action check_exit = [this]() {this->CheckExit(); };
	this->SetInput(handle_input);
	this->SetPhysics(gravity_pull);
	this->SetUser(check_exit);
	
}

void Game::MainLoop(void) {
	//while (!IsFinished())
	while(!this->doneFlag)
		this->MainLoopIteration();
}



void Game::MainLoopIteration(void) {
	//Render();
	//Input();
	//ProgressAnimations();
	//AI();
	//Physics();
	//CollisionChecking();
	//UserCode(); // hook for custom code at end
	//CommitDestructions();
	
	al_wait_for_event(this->queue, &this->event);
	
	int y = this->player1->GetY();
	int x = this->player1->GetX();
	int step = this->player1->GetSpeed();
	
	assert(x >= 0 && y >= 0);
	switch (this->event.type)
	{
	case ALLEGRO_EVENT_TIMER:

		this->Input();
		this->Physics();
		this->UserCode();
		
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->doneFlag = true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		key[event.keyboard.keycode] = true ;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (event.keyboard.keycode == ALLEGRO_KEY_DOWN){ //ean afisame to katw belaki
			this->player1->ChangeStance(); // allazume state
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_A) { // stamatise na kouniete
			this->player1->StopMoving();
		}
		key[event.keyboard.keycode] &= false;
		break;
	default:
		break;
	}
	if (this->doneFlag) {
		return;
	}

	if (this->redraw && al_is_event_queue_empty(this->queue))
	{
		
		this->Render();
		this->redraw = false;
	}

	//USER HOOKS
	this->player1->CheckSpellTimer(this->timer->getDelta());
	
	this->timer->fps();

}

void Game::HandleInput(void) {
	int y = this->player1->GetY();
	int x = this->player1->GetX();
	
	if (key[ALLEGRO_KEY_UP] && this->TryMoveUp(x, y) && !this->TryMoveDown(x, y)) {
		this->jump_y = this->player1->GetJumpHeight();
	}
	if (key[ALLEGRO_KEY_DOWN] && !this->TryMoveDown(x, y) && !this->player1->isDucking()) {
		this->player1->ChangeStance();
	}
	if (key[ALLEGRO_KEY_LEFT] && this->TryMoveLeft(x, y)) {
		this->player1->MoveLeft();
	}
	if (key[ALLEGRO_KEY_RIGHT] && this->TryMoveRight(x, y)) {
		this->player1->MoveRight();
	}

	if (key[ALLEGRO_KEY_0]) {
		this->music_player->Stop();
	}
	if (key[ALLEGRO_KEY_A]) {
		std::cout << "allegro key A\n";
		this->player1->Attack();
	}
	//TO CHECK IF MAPS CHANGE 
	if (key[ALLEGRO_KEY_1]) {
		this->ChangeMap(MapLocations::main_screen);
		this->redraw = true;
		
	}

	if (key[ALLEGRO_KEY_2]) {
		this->ChangeMap(MapLocations::palace);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_3]) {
		this->ChangeMap(MapLocations::first_floor);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_4]) {
		this->ChangeMap(MapLocations::loading);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_5]) {
		this->ChangeMap(MapLocations::first_floor_right);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_6]) {
		this->player1->castSpell(3);
	}
	if (key[ALLEGRO_KEY_P]) {
		PauseGame();
		this->redraw = true;
		return;
	}

	if (key[ALLEGRO_KEY_ESCAPE])
		this->doneFlag = true;
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
		key[i] &= KEY_SEEN;
	this->redraw = true;
	return;
}

void Game::ChangeMap(MapLocations new_map) {
	this->background_map->ChangeMap(new_map);
	this->player1->Respawn(this->background_map->GetSpawn());
	return;
}

void Game::ChangeMap(std::string new_map, Point *spawn_location) {
	this->background_map->ChangeMap(new_map);
	this->player1->Respawn(spawn_location);
	return;
}

void Game::Render(void) {
	this->StartRender();
	al_hold_bitmap_drawing(1);
	
	this->background_map->RenderBg(this->player1->GetCameraX(), this->screen->GetScaledWidth(), 0, this->screen->GetScaledHeight());
	this->background_map->Render(this->player1->GetCameraX(), this->screen->GetScaledWidth(), 0, this->screen->GetScaledHeight());
	this->player1->Render(this->timer->getDelta());
	
	al_hold_bitmap_drawing(0);
	this->DrawBufferToScreen();
}

void Game::StartRender(void) {
	al_set_target_bitmap(this->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
}

void Game::DrawBufferToScreen(void) {
	al_set_target_backbuffer(this->screen->GetDisplay());
	

	int const max_x = this->screen->GetWidth();
	int const max_y = this->screen->GetHeight();
	int const scale = this->screen->GetScalingFactor();
	
	
	if (this->game_state == game_state::paused) {
		
		al_draw_tinted_scaled_bitmap(this->buffer,
			al_map_rgb(80, 80, 80),
			0, 0,
			max_x/ scale, max_y/ scale,
			0, 0,
			max_x, max_y,
			0);
		
		
		al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255), max_x / 2, max_y / 2.2, ALLEGRO_ALIGN_CENTRE, "Game Paused");
	}
	else {
		al_hold_bitmap_drawing(1);
		al_draw_scaled_bitmap(this->buffer, 0, 0, max_x / scale, max_y / scale, 0, 0, max_x, max_y, 0);
		al_hold_bitmap_drawing(0);
	}
	
	
	al_flip_display();
}

void Game::LoadSetting(void) {
	
}

void Game::Register() {
	al_install_keyboard(); // install keyboard
	al_install_mouse(); // install mouse

	//register keyboard events at queue
	al_register_event_source(this->queue, al_get_keyboard_event_source()); 
	
	//register display events at queue
	al_register_event_source(this->queue, al_get_display_event_source(this->screen->GetDisplay()));
	
	//register timer events at queue{
	al_register_event_source(this->queue, al_get_timer_event_source(this->timer->getTimer())); 
	
	//after registring time we start it
	al_start_timer(this->timer->getTimer());

}


bool Game::TryMoveDown(int x, int y) {
	if (y + 32 >= this->y_bound)
		return false;
	int lx = x / 16;									// left x
	int dy = (y + this->player1->GetHeight()) / 16;		// left down y + height (tiles)
	int rx = (x + 15) / 16;								// right x
	return !(this->background_map->IsSolid(lx, dy) || this->background_map->IsSolid(rx, dy));
}

bool Game::TryMoveUp(int x, int y){
	if (y <= 0)
		return false;
	int lx = x / 16;			// left x
	int uy = (y - 1) / 16;		// left upper y - 1
	int rx = (x + 15) / 16;		// right x
	return !(this->background_map->IsSolid(lx, uy) || this->background_map->IsSolid(rx, uy));
}

bool Game::TryMoveLeft(int x, int y){
	this->player1->AnimateMoveLeft();
	if (x <= 0)
		return false;
	int lx = (x - 1) / 16;		// left x - 1
	int uy = (y) / 16;			// upper y
	int my = (y + 15) / 16;		// middle y
	int dy = (y + 31) / 16;		// down y

	return !(this->background_map->IsSolid(lx, uy) || this->background_map->IsSolid(lx, my) || this->background_map->IsSolid(lx, dy));
}

bool Game::TryMoveRight(int x, int y) {
	this->player1->AnimateMoveRight();
	if (x + 16 >= this->x_bound)
		return false;
	int rx = (x + 16) / 16;		// right x + 1
	int uy = (y) / 16;			// upper y
	int my = (y + 15) / 16;		// middle y
	int dy = (y + 31) / 16;		// down y

	return !(this->background_map->IsSolid(rx, uy) || this->background_map->IsSolid(rx, my) || this->background_map->IsSolid(rx, dy));
	
}

void Game::PauseGame() {
	this->game_state = game_state::paused;
	Action action = [this]() {this->HandlePauseInput(); };
	this->SetInput(action);
	this->SetPhysics(NULL);
	memset(key, 0, sizeof(key));
};

void Game::ResumeGame() {
	Action handle_input = [this]() {this->HandleInput(); };
	Action gravity_pull = [this]() {this->GravityPull(); };
	this->SetInput(handle_input);
	this->SetPhysics(gravity_pull);
	game_state = game_state::playing;
	memset(key, 0, sizeof(key));
};

void Game::RenderPauseScreen(void) {
	
	this->DrawBufferToScreen();
};

void Game::HandlePauseInput(void) {

	if (key[ALLEGRO_KEY_P]) {
		this->ResumeGame();
	}

	if (key[ALLEGRO_KEY_ESCAPE])
		this->doneFlag = true;
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
		key[i] &= KEY_SEEN;
	this->redraw = true;
}

void Game::GravityPull() {
	int x = this->player1->GetX();
	int y = this->player1->GetY();
	int max_y = this->y_bound - 32;
	int jump_speed = this->player1->GetJumpSpeed();
	
	if (this->jump_y > 0)
		for (int i = 0; i < jump_speed; i++) {
			if (this->TryMoveUp(x, y)) {
				this->player1->MoveUp();
				this->jump_y--;
			}
			else
				this->jump_y = 0;
			y = this->player1->GetY();
		}
	else if (this->TryMoveDown(x, y))
	{
		int fall_speed = this->player1->GetFallSpeed();
		for (int i = 0; i < fall_speed; i++) {
			if (this->TryMoveDown(x, y)) {
				this->player1->MoveDown();
			}
			y = this->player1->GetY();
		}
	}
	else { // an teleiwse na peftei
		if(this->player1->GetState() == p_state::land_left || this->player1->GetState() == p_state::land_right)
			this->player1->StopMoving();
	}

}

void Game::CheckExit() {
	int lx = (this->player1->GetX()) / 16;
	int rx = (this->player1->GetX() + 15) / 16;
	int uy = (this->player1->GetY()) / 16;
	int dy = (this->player1->GetY() + this->player1->GetHeight() - 1) / 16;
	Point* chosen_exit = NULL;
	if (this->background_map->IsExit(Point(lx, uy)))
		chosen_exit = new Point(lx, uy);
	else if (this->background_map->IsExit(Point(lx, dy)))
		chosen_exit = new Point(lx, dy);
	else if (this->background_map->IsExit(Point(rx, uy)))
		chosen_exit = new Point(rx, uy);
	else if (this->background_map->IsExit(Point(rx, dy)))
		chosen_exit = new Point(rx, dy);
	if (chosen_exit != NULL) {
		ExitPoint exit = this->background_map->GetExit(*chosen_exit);
		std::cout << "Changing map: " << exit.GetNextMapName() << std::endl;
		std::cout << "Spawn At: " << *exit.GetNextSpawn() << std::endl;
		std::cout << "lx: " << lx << " rx: " << rx << " uy: " << uy << " dy: " << dy << std::endl;
		
		this->ChangeMap(exit.GetNextMapName(), exit.GetNextSpawn());
	}
	
	
		
}