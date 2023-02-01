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
	

	this->stats_display_height_offset = data["stats_display"]["height"]; // how much will displaying stats take of off screen
	
	this->timer = new Timer(data["ticker"]["rate"]); 
	this->timer->setPrintFPS(data["ticker"]["showfps"]); 
	this->screen = new Screen(data["screen"]["width"], data["screen"]["height"] + this->stats_display_height_offset, data["screen"]["scale"]);
	

	this->queue = al_create_event_queue();
	Register();
	
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP); // faster bitmaps display must be initialised
	
	this->buffer = al_create_bitmap(data["screen"]["width"] / 2, (data["screen"]["height"] - this->stats_display_height_offset) / 2);
	Point* spawn_location;
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
								data["screen"]["relative_location"]
							   );
	this->player1->LoadStats(data["screen"]["width"] / data["screen"]["scale"], MUL_16(this->background_map->getTileMap()->getTilemapHeight()), this->stats_display_height_offset/ data["screen"]["scale"]);
	this->music_player = new MusicPlayer();
	
	this->player1->RegisterSpell(std::bind(&Game::CastThunder, this), 120);
	
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	

	this->jump_y = 0;
	this->key_pressed = false;
	
	Action handle_input = [this]() {this->HandleInput(); };
	Action gravity_pull = [this]() {this->HandlePhysics(); };
	Action check_exit = [this]() {this->CheckExit(); };
	Action handle_ai = [this]() {this->HandleAI(); };
	this->SetInput(handle_input);
	this->SetPhysics(gravity_pull);
	this->SetUser(check_exit);
	this->SetAI(handle_ai);
	f.close();
	
}
void Game::CastThunder() {
	this->player1->DisplayTimedMessage("Casted Thunder", 1);
	this->background_map->KillAllEnemies(this->player1);
}

void Game::MainLoop(void) {
	//while (!IsFinished())
	while(!this->doneFlag)
		this->MainLoopIteration();
}

void Game::InitiateDestructionMusic() {
	if (!this->changed_music && this->background_map->getState() == MapLocations::boss_room) {
		this->music_player->Play(1);
		this->changed_music = true;
		this->player1->DisplayTimedMessage("Now playing Boss music", 3);
	}
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
		if (this->game_state == game_state::playing) {
			this->AI();
			this->Physics();
			this->UserCode();
		}
		
		//USER HOOKS
		this->player1->CheckSpellTimer(this->timer->getDelta());

		this->timer->fps();
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->doneFlag = true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		key[event.keyboard.keycode] = true ;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (this->game_state == game_state::paused) break;
		if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && this->player1->isDucking()){ //ean afisame to katw belaki
			this->player1->ChangeStance(); // allazume state
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT ) { // stamatise na kouniete
			this->player1->StopMoving();
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_A) {
			this->key_pressed = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_F) {
			this->toggle_player_collision_box = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
			this->key_q = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_W) {
			this->key_w = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_E) {
			this->key_e = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_R) {
			this->key_r = false;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_T) {
			this->key_t = false;
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

	

}

void Game::HandleAI(void) {
	this->InitiateDestructionMusic();
	if (ai_flag) { // ai moves once per 2 loops
		this->background_map->AiUpdate(this->player1); //FIX TODO proswrino tha mpei sto AI kai tha ginete me dynamic bind
		
		this->ai_flag = false;
	}
	else {
		this->ai_flag = true;
	}
}

void Game::HandleInput(void) {
	int y = this->player1->GetY();
	int x = this->player1->GetX();
	int width = this->player1->GetWidth();
	int height = this->player1->GetHeight();
	
	if (key[ALLEGRO_KEY_UP] && this->background_map->TryMoveUp(x, y, width, height) && !this->background_map->TryMoveDown(x, y, width, height) && !this->background_map->CheckObjectCollision(*this->player1)) {
		this->jump_y = this->player1->GetJumpHeight();
	}
	if (key[ALLEGRO_KEY_DOWN] && !this->player1->isDucking() && !this->background_map->TryMoveDown(x, y, width, height) && !this->background_map->CheckObjectCollision(*this->player1) ) {
		this->player1->ChangeStance();
	}
	if (key[ALLEGRO_KEY_LEFT]) {
		this->player1->AnimateMoveLeft();
		if(this->background_map->TryMoveLeft(x, y, width, height))
			this->player1->MoveLeft();
	}
	if (key[ALLEGRO_KEY_RIGHT]) {
		this->player1->AnimateMoveRight();
		if (this->background_map->TryMoveRight(x, y, width, height))
			this->player1->MoveRight();
	}
	if (key[ALLEGRO_KEY_F] && !this->toggle_player_collision_box) {
		this->toggle_player_collision_box = true;
		this->player1->ToggleCollisionBoxRender();
	}


	if (key[ALLEGRO_KEY_0]) {
		this->music_player->Stop();
	}
	if (key[ALLEGRO_KEY_A] && !this->key_pressed) {
		Point of_attack = this->player1->GetAttackPoint();
		if (this->background_map->TryAttack(of_attack.GetX(), of_attack.GetY())) {
			this->player1->Attack();
			this->background_map->PlayerAttack(this->player1);
		}
		else {
			this->player1->CancelledAttack();
		}
		
		this->key_pressed = true;
	}
	if (this->background_map->getState() == MapLocations::main_screen && key[ALLEGRO_KEY_ENTER] ) {
		this->ChangeMap(MapLocations::palace);
		this->redraw = true;
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
		this->ChangeMap(MapLocations::win_screen);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_5]) {
		this->ChangeMap(MapLocations::first_floor_right);
		this->redraw = true;
	}
	if (key[ALLEGRO_KEY_6]) {
		this->ChangeMap(MapLocations::loose_screen);
		this->redraw = true;
	}
	//spells
	if (key[ALLEGRO_KEY_Q] && !this->key_q) {
		this->player1->castSpell(0);
		this->key_q = true;
	}
	if (key[ALLEGRO_KEY_W] && !this->key_w) {
		this->player1->castSpell(1);
		this->key_w = true;
	}
	if (key[ALLEGRO_KEY_E] && !this->key_e) {
		this->player1->castSpell(2);
		this->key_e = true;
	}
	if (key[ALLEGRO_KEY_R] && !this->key_r) {
		this->player1->castSpell(3);
		this->key_r = true;
	}
	if (key[ALLEGRO_KEY_T] && !this->key_t) {
		this->player1->castSpell(4);
		this->key_t = true;
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

	//briskei to camera_x to opoio einai poso exei proxwrisei to screen se sxesi me ta relative location tu map
	int camera_x = this->background_map->GetCameraOffsetX(this->player1->GetCameraX(), this->screen->GetScaledWidth());
	
	this->background_map->RenderBg(this->player1->GetCameraX(), this->screen->GetScaledWidth(), 0, this->screen->GetScaledHeight());
	this->background_map->Render(this->player1->GetCameraX(), this->screen->GetScaledWidth(), 0, this->screen->GetScaledHeight());
	this->background_map->RenderEntities(this->timer->getDelta(), camera_x);

	
	

	bool player_can_move_right = this->background_map->TryMoveRight(this->player1->GetX(), this->player1->GetY(), this->player1->GetWidth(), this->player1->GetHeight());
	bool player_can_move_left = this->background_map->TryMoveLeft(this->player1->GetX(), this->player1->GetY(), this->player1->GetWidth(), this->player1->GetHeight());
	bool player_can_move_up = this->background_map->TryMoveUp(this->player1->GetX(), this->player1->GetY(), this->player1->GetWidth(), this->player1->GetHeight());
	
	this->player1->Render(this->timer->getDelta(), player_can_move_right, player_can_move_left, player_can_move_up);
	
	
	al_hold_bitmap_drawing(0);
	this->DrawBufferToScreen();
}

void Game::StartRender(void) {
	this->player1->LoadStats();
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




void Game::PauseGame() {
	this->game_state = game_state::paused;
	Action action = [this]() {this->HandlePauseInput(); };
	this->SetInput(action);
	this->SetPhysics(NULL);
	memset(key, 0, sizeof(key));
};

void Game::ResumeGame() {
	Action handle_input = [this]() {this->HandleInput(); };
	Action gravity_pull = [this]() {this->HandlePhysics(); };
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

void Game::HandlePhysics(void) {
	this->HandlePlayerPhysics();
	this->HandleMapEnemiesPhysics();
	this->HandleMapItemPhysics();
	this->background_map->CheckPlayerCollisionsWithEntities(this->player1);
	if (!this->player1->isAlive()) {
		if (this->player1->canRespawn())
			this->ChangeMap(this->background_map->getState());
		else
			this->ChangeMap(MapLocations::loose_screen);
	}
	else if (this->player1->hasTheSword()) {
		this->ChangeMap(MapLocations::win_screen);
		this->player1->DropTheSword();
	}
}

void Game::HandlePlayerPhysics(void) {
	int x = this->player1->GetX();
	int y = this->player1->GetY();
	int width = this->player1->GetWidth();
	int height = this->player1->GetHeight();

	if (this->jump_y > 0) {
		int jump_speed = this->player1->GetJumpSpeed();
		for (int i = 0; i < jump_speed; i++) {
			if (this->background_map->TryMoveUp(x, y, width, height)) {
				this->player1->MoveUp();
				this->jump_y--;
			}
			else
				this->jump_y = 0;
			y = this->player1->GetY();
		}
	}
	else if (this->background_map->PlayerMoveDown(*this->player1))
	{
		int fall_speed = this->player1->GetFallSpeed();
		for (int i = 0; i < fall_speed; i++) {
			if (this->background_map->PlayerMoveDown(*this->player1)) {
				this->player1->MoveDown();
			}
			else
				break;
			y = this->player1->GetY();
		}
	}
	else { // an teleiwse na peftei
		if (this->player1->GetState() == p_state::land_left || this->player1->GetState() == p_state::land_right)
			this->player1->StopMoving();
	}
}

void Game::HandleMapEnemiesPhysics(void) {
	for (Entity* entity : this->background_map->GetMapEnemies()) {
		int x = entity->GetX();
		int y = entity->GetY();
		int width = entity->GetWidth();
		int height = entity->GetHeight();
		int fall_speed = this->player1->GetFallSpeed();
		if (this->background_map->TryMoveDown(x, y, width, height))
		{
			for (int i = 0; i < fall_speed; i++) {
				if (this->background_map->TryMoveDown(x, y, width, height)) {
					entity->MoveDown();
				}
				else
					break;
				y = entity->GetY();
			}
		}
	}
}

void Game::HandleMapItemPhysics(void) {
	for (Entity* entity : this->background_map->GetMapItems()) {
		int x = entity->GetX();
		int y = entity->GetY();
		int width = entity->GetWidth();
		int height = entity->GetHeight();
		int fall_speed = this->player1->GetFallSpeed();
		if (this->background_map->TryMoveDown(x, y, width, height))
		{
			for (int i = 0; i < fall_speed; i++) {
				if (this->background_map->TryMoveDown(x, y, width, height)) {
					entity->MoveDown();
				}
				else
					break;
				y = entity->GetY();
			}
		}
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
		
		this->ChangeMap(exit.GetNextMapName(), exit.GetNextSpawn());
	}
	
	
		
}