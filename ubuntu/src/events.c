#include "../inc/header.h"

void doKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			main_ship.up = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			main_ship.down = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			main_ship.left = 0;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			main_ship.right = 0;
		}

        if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
            main_ship.shoot = 0;
        }
	}
}

void doKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			main_ship.up = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			main_ship.down = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			main_ship.left = 1;
		}
		
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			main_ship.right = 1;
		}
        if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
            main_ship.shoot = 1;
        }
	}
}

void doInput(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
				
			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;
				
			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
			default:
				break;
		}
		if(event.key.keysym.sym == SDLK_ESCAPE) {
    	IS_PAUSE = true;
   		break;
  	}
	}

	
}
