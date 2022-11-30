#include "CS454.h"



int main()
{
	init_all();
	//UnitTest1();
	Map* map;

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
	

	al_install_keyboard(); // install keyboard
	al_install_mouse(); // install mouse
	
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); //30fps timer
	
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //event queue

	
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H); //init display 

	al_register_event_source(queue, al_get_keyboard_event_source()); //register keyboard events at queue
	al_register_event_source(queue, al_get_display_event_source(display)); //register display events at queue
	al_register_event_source(queue, al_get_timer_event_source(timer)); //register timer events at queue

	bool redraw = true; //redraw flag
	bool done = false; //done flag
	ALLEGRO_EVENT event; //event
	
	al_start_timer(timer);

	int y = 0;
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
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			y++;
			
			map->BlitSelf(0, 0);
			al_flip_display();

			redraw = false;
		}
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