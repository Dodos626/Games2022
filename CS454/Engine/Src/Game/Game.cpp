#include "Game.h"

Game::Game() {
	

	try {
		Initialise();
		
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		throw("terminating error in game\n");
	}
	MainLoop();
	
}

void Game::Initialise(void) {
	assert(al_init());
	assert(al_init_image_addon());
	assert(al_init_primitives_addon());

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
		this->background_map = new Map(
			background_json["CSVsource"],
			background_json["CSVwidth"],
			background_json["CSVheight"],
			background_json["PNGsource"].get<std::string>().c_str(),
			background_json["PNGwidth"],
			background_json["PNGheight"],
			background_json["SolidIds"]
		);
		player_x = background_json["spawn_x"];
		player_y = background_json["spawn_y"];
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
	
	this->background_map->PrecomputeMap();
	
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	
	this->y_bound = MUL_16(this->background_map->getTileMap()->getTilemapHeight());
	this->x_bound = MUL_16(this->background_map->getTileMap()->getTilemapWidth());
	
	
}

void Game::MainLoop(void) {
	//while (!IsFinished())
	while(!this->doneFlag)
		MainLoopIteration();
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
		
		
		if (key[ALLEGRO_KEY_UP] && y > 0 && this->TryMoveUp(x, y)) {
			this->player1->MoveUp();
		}
		if (key[ALLEGRO_KEY_DOWN] && y + 16 <  this->y_bound && this->TryMoveDown(x, y)) {
			this->player1->MoveDown();
		}
		if (key[ALLEGRO_KEY_LEFT] && x > 0 && this->TryMoveLeft(x, y)) {
			this->player1->MoveLeft();
		}
		if (key[ALLEGRO_KEY_RIGHT] && x + 16 < this->x_bound && this->TryMoveRight(x, y)) {
			this->player1->MoveRight();
		}
			
			
		if (key[ALLEGRO_KEY_ESCAPE])
			this->doneFlag = true;
		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
			key[i] &= KEY_SEEN;
		this->redraw = true;
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
	
	al_hold_bitmap_drawing(1);
	al_draw_scaled_bitmap(this->buffer, 0, 0, max_x / 2, max_y / 2, 0, 0, max_x, max_y, 0);
	al_hold_bitmap_drawing(0);
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
	int ldx = x / 16;			// left down x
	int ldy = (y + 16) / 16;	// left down y + 1
	int rdx = (x + 15) / 16;	// right down x
	int rdy = (y + 16) / 16;	// right down y + 1
	return !(this->background_map->IsSolid(ldx, ldy) || this->background_map->IsSolid(rdx, rdy));
}

bool Game::TryMoveUp(int x, int y){
	int lux = x / 16;			// left upper x
	int luy = (y - 1) / 16;		// left upper y - 1
	int rux = (x + 15) / 16;	// right upper x
	int ruy = (y - 1) / 16;		// right upper y - 1

	return !(this->background_map->IsSolid(lux, luy) || this->background_map->IsSolid(rux, ruy));
}

bool Game::TryMoveLeft(int x, int y){
	int lux = (x - 1) / 16;		// left upper x - 1
	int luy = (y) / 16;			// left upper y
	int ldx = (x - 1) / 16;		// left down x - 1
	int ldy = (y + 15) / 16;	// left down y

	return !(this->background_map->IsSolid(lux, luy) || this->background_map->IsSolid(ldx, ldy));
}

bool Game::TryMoveRight(int x, int y) {
	int rux = (x + 16) / 16;	// right upper x + 1
	int ruy = (y) / 16;			// right upper y
	int rdx = (x + 16) / 16;	// right down x + 1
	int rdy = (y + 15) / 16;	// right down y

	return !(this->background_map->IsSolid(rux, ruy) || this->background_map->IsSolid(rdx, rdy));
	
}