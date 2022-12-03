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

	this->timer = new Timer(60.0); // pros to parwn hardcoded
	this->timer->setPrintFPS(true);
	this->screen = new Screen(1200, 800); // pros to parwn hardcoded
	this->screen->SetScalingFactor(16); // pros to parwn hardcoded

	this->queue = al_create_event_queue();
	Register();
	
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP); // faster bitmaps display must be initialised
	try {
		//bitmap tileset 12x21
		this->background_map = new Map(
			"UnitTests/UnitTest1Media/media/map1_Kachelebene 1.csv",
			21,
			42,
			"UnitTests/UnitTest1Media/media/overworld_tileset_grass.png",
			12,
			21
		);
		//bitmap = new BitMap("UnitTests/UnitTest1Media/media/overworld_tileset_grass.png");

	}
	catch (std::string e) {
		std::cout << e << std::endl;
		throw( "Init of game failed, abort!\n");
		
	}

	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	
}

void Game::MainLoop(void) {
	//while (!IsFinished())
	while(!this->doneFlag)
		MainLoopIteration();
}
int y = 0;
int x = 0;

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
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	
	switch (this->event.type)
	{
	case ALLEGRO_EVENT_TIMER:
		// game logic goes here.
		this->redraw = true;
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		this->doneFlag = true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		this->redraw = true;
		if (event.keyboard.keycode == ALLEGRO_KEY_UP && y!=0) {
			y--;	
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			y++;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && x!=0) {
			x--;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			x++;
		if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			this->doneFlag = true;
		break;
	default:
		break;
	}
	if (this->doneFlag) {
		return;
	}

	if (this->redraw && al_is_event_queue_empty(this->queue))
	{
		this->background_map->BlitSelf(x, y, this->screen->GetScalingFactor(), this->screen->GetWidth(), this->screen->GetHeight()); // pros to parwn hardcoded
		al_flip_display();
		this->redraw = false;
	}

	this->timer->fps();
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