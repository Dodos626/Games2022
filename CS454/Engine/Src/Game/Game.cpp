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
	

	this->timer = new Timer(data["ticker"]["rate"]); 
	this->timer->setPrintFPS(data["ticker"]["showfps"]); 
	this->screen = new Screen(data["screen"]["width"], data["screen"]["height"]);
	this->screen->SetScalingFactor(16); // pros to parwn hardcoded

	this->queue = al_create_event_queue();
	Register();
	
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP); // faster bitmaps display must be initialised
	
	this->buffer = al_create_bitmap(data["screen"]["width"]/2, data["screen"]["height"]/2);
	int player_x = 0, player_y = 0;
	try {
		auto background_json = data["bitmaps"]["background"];
		this->background_map = new Map("Engine/Configs/MapConfig.json");
		player_x = this->background_map->getSpawn().x;
		player_y = this->background_map->getSpawn().y;
	}
	catch (std::string e) {
		throw( "Init of game failed, abort!\n");
		
	}
	memset(this->key, 0, sizeof(this->key)); // initiate input key buffer
	
	this->player1 = new Player(player_x,
							   player_y,
							   this->screen->GetWidth() / 2,
							   MUL_16(this->background_map->getTileMap()->getTilemapWidth()),
							   data["screen"]["relative_location"]
							   );

	this->music_player = new MusicPlayer();
	
	
	
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	
	this->y_bound = MUL_16(this->background_map->getTileMap()->getTilemapHeight());
	this->x_bound = MUL_16(this->background_map->getTileMap()->getTilemapWidth());
	this->jump_y = 0;
	this->jump_height = data["physics"]["jump_height"];
	this->jump_speed = data["physics"]["jump_speed"];
	this->fall_speed = data["physics"]["fall_speed"];
	Action handle_input = [this]() {this->HandleInput(); };
	Action gravity_pull = [this]() {this->GravityPull(); };
	this->SetInput(handle_input);
	this->SetPhysics(gravity_pull);
	
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
		
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->doneFlag = true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		key[event.keyboard.keycode] &= KEY_RELEASED;
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
	
	this->timer->fps();
}

void Game::HandleInput(void) {
	int y = this->player1->GetY();
	int x = this->player1->GetX();
	
	if (key[ALLEGRO_KEY_UP] && this->TryMoveUp(x, y) && !this->TryMoveDown(x, y)) {
		this->jump_y = this->jump_height;
	}
	if (key[ALLEGRO_KEY_DOWN] && this->TryMoveDown(x, y)) {
		//this->player1->MoveDown(); TO DELETE
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

	//TO CHECK IF MAPS CHANGE 
	if (key[ALLEGRO_KEY_1]) {
		this->background_map->ChangeMap(map_state::main_screen);
	}

	if (key[ALLEGRO_KEY_2]) {
		this->background_map->ChangeMap(map_state::playing);
	}
	if (key[ALLEGRO_KEY_3]) {
		this->background_map->ChangeMap(map_state::first_floor);
	}
	if (key[ALLEGRO_KEY_4]) {
		this->background_map->ChangeMap(map_state::loading);
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
}

void Game::Render(void) {
	this->StartRender();
	al_hold_bitmap_drawing(1);
	
	this->background_map->Render(this->player1->GetCameraX(), this->screen->GetWidth() / 2, 0, this->screen->GetHeight() / 2);
	this->player1->Render();
	
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
	
	
	if (this->game_state == game_state::paused) {
		
		al_draw_tinted_scaled_bitmap(this->buffer,
			al_map_rgb(80, 80, 80),
			0, 0,
			max_x/2, max_y/2,
			0, 0,
			max_x, max_y,
			0);
		
		al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255), max_x / 2, max_y / 2.2, ALLEGRO_ALIGN_CENTRE, "Game Paused");
	}
	else {
		al_hold_bitmap_drawing(1);
		al_draw_scaled_bitmap(this->buffer, 0, 0, max_x / 2, max_y / 2, 0, 0, max_x, max_y, 0);
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
	int lx = x / 16;			// left x
	int dy = (y + 32) / 16;		// left down y + 2 (tiles)
	int rx = (x + 15) / 16;		// right x
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
	if (x <= 0)
		return false;
	int lx = (x - 1) / 16;		// left x - 1
	int uy = (y) / 16;			// upper y
	int my = (y + 15) / 16;		// middle y
	int dy = (y + 31) / 16;		// down y

	return !(this->background_map->IsSolid(lx, uy) || this->background_map->IsSolid(lx, my) || this->background_map->IsSolid(lx, dy));
}

bool Game::TryMoveRight(int x, int y) {
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
	if (this->jump_y > 0)
		for (int i = 0; i < this->jump_speed; i++) {
			if (this->TryMoveUp(x, y)) {
				this->player1->MoveUp();
				this->jump_y--;
			}
			else
				this->jump_y = 0;
			y = this->player1->GetY();
		}
	else if (this->TryMoveDown(x, y))
		for (int i = 0; i < this->fall_speed; i++) {
			if (this->TryMoveDown(x, y)) {
				this->player1->MoveDown();
			}
			y = this->player1->GetY();
		}

}