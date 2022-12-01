#include "CS454.h"



int main()
{
	init_all();
	//UnitTest1();
	Map* map;
	
	//al_set_new_bitmap_flags(ALLEGRO_NO_PRESERVE_TEXTURE); // faster bitmaps
	
	
	

	al_install_keyboard(); // install keyboard
	al_install_mouse(); // install mouse
	
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); //60fps timer
	
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //event queue

	
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H); //init display 
	
	
	//META TO INIT TU DISPLAY I ALLEGRO MPOREI NA BALEI BITMAP STIN GPU
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP); // faster bitmaps
	try {
		//bitmap tileset 12x21
		map = new Map(
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
		std::cout << "UnitTest1 has failed\n";
		return -1;
	}
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP); // reset to default
	
	al_register_event_source(queue, al_get_keyboard_event_source()); //register keyboard events at queue
	al_register_event_source(queue, al_get_display_event_source(display)); //register display events at queue
	al_register_event_source(queue, al_get_timer_event_source(timer)); //register timer events at queue

	bool redraw = true; //redraw flag
	bool done = false; //done flag
	ALLEGRO_EVENT event; //event
	
	al_start_timer(timer);

	int y = 0;
	int x = 0;

	int max_x = map->getTileMap()->getTilemapWidth()*16*2 - SCREEN_W;
	int max_y = map->getTileMap()->getTilemapHeight()*16*2 - SCREEN_H;

	if (max_x < 0) max_x = 0;
	if (max_y < 0) max_y = 0;
	
	std::cout << "max_x: " << max_x << std::endl;
	std::cout << "max_y: " << max_y << std::endl;
	
	double old_time = al_get_time();
	
	while (true) {

		al_wait_for_event(queue, &event);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// game logic goes here.
			redraw = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			redraw = true;
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				if (y == 0) {
					break;
				}
				y -= 1;
				break;
			
			case ALLEGRO_KEY_DOWN:
				if (y == max_y)
					break;
				y += 1;
				break;
			case ALLEGRO_KEY_LEFT:
				if (x == 0)
					break;
				x -= 1;
				break;
			case ALLEGRO_KEY_RIGHT:
				if (x == max_x)
					break;
				x += 1;
				break;
			}
			break;
			
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			
			//std::cout << "x: " << x << " y: " << y << std::endl;
			map->BlitSelf(x, y,2,SCREEN_W,SCREEN_H);
			al_flip_display();
			

			redraw = false;
		}

		
		old_time = fps(old_time);
		
	}
	

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}

int init_all() {
	if (!al_init()) { // Initialize allegro
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	if (!al_init_image_addon())
	{
		printf("couldn't initialize image addon\n");
		return -1;
	}
	
	return 1;
}

double fps(double old_time) {
	double new_time = al_get_time();
	double delta = new_time - old_time;
	double fps = 1 / (delta);
	fps_timer += delta;
	avg_fps = (fps + avg_fps) / 2;

	if (fps_timer > 0.5) {
		fps_timer = 0;
		std::cout << avg_fps << std::endl;
		avg_fps = 0;
	}
	return new_time;
}
