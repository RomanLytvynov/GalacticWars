#include "../inc/header.h"

bool init_mgo() {
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        return false;
    }
    return true;
}

void cleanUpgo(Mix_Chunk *click) {
	Mix_FreeChunk( click );
    Mix_CloseAudio();
}

void Play_Soundgo(Mix_Chunk *click) {
	if( Mix_PlayChannel( -1, click, 0 ) == -1 ) {
    	printf("PlayVoice error\n");
        return;    
    }
}

void game_over(SDL_Renderer *ren)
{
	SDL_Event event;
	int x = 0, y = 0;
	SDL_Texture *background = loadTexture("resource/images/gameover/game_over.png", ren);
	SDL_Texture *temp2 = loadTexture("resource/images/gameover/exit_button.png", ren);
	SDL_Texture *score_text = loadTexture("resource/images/gameover/score.png", ren);

	SDL_Texture *exit = loadTexture("resource/images/menu/exit_button.png", ren);
	SDL_Texture *exit_pressed = loadTexture("resource/images/menu/exit_button_pressed.png", ren);
	SDL_Texture *exit_on = loadTexture("resource/images/menu/exit_button_on.png", ren);

	if(!init_mgo()) printf("Without music\n");
	//Mix_Music *music = Mix_LoadMUS( "resource/audio/ost/start.mp3" );
	Mix_Chunk *click = Mix_LoadWAV( "resource/audio/sounds/click_1.wav" );
	Mix_VolumeMusic(30);
	char sc_str[256];
	while(kostyl)
	{
		SDL_RenderClear(ren);
        renderTexture(background, ren, 0, 0, 800, 1000);
        renderTexture(score_text, ren, 295, 430, 142, 30);
		SDL_Color color = { 255, 255, 255, 255 };
		sprintf(sc_str, "%i", score);
		renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color, 38, ren_mainplane),ren_mainplane, 300,555);
        renderTexture(exit, ren, 265, 760, 270, 71);
        SDL_RenderPresent(ren);
		kostyl = false;
	}
	while (IS_GAME_OVER) {
		while(SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT)
			{
				RUN = false;
				return;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				x = event.motion.x;
				y = event.motion.y;

				if((x > 265 && x < 535) && (y > 760 && y < 831))
				{
					Play_Soundgo(click);
					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(score_text, ren, 295, 430, 142, 30);
					renderTexture(exit_pressed, ren, 265, 760, 270, 71);
					SDL_RenderPresent(ren);
					SDL_Delay(100);

					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(score_text, ren, 295, 430, 142, 30);
					renderTexture(temp2, ren, 265, 760, 270, 71);
					SDL_RenderPresent(ren);
					SDL_Delay(100);

					RUN = false;
					IS_GAME_OVER = false;
					cleanUpgo(click);
					return;
				}
			}
			if(event.type == SDL_MOUSEMOTION)
			{
				x = event.motion.x;
				y = event.motion.y;
				if((x > 264 && x < 534) && (y > 760 && y < 831))
				{
					exit = exit_on;
				}

			}

			SDL_RenderClear(ren);
			renderTexture(background, ren, 0, 0, 800, 1000);
			renderTexture(score_text, ren, 295, 430, 142, 30);
			SDL_Color color = { 255, 255, 255, 255 };
			sprintf(sc_str, "%i", score);
			renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color, 38, ren_mainplane),ren_mainplane, 300,555);
			renderTexture(exit, ren, 265, 760, 270, 71);
			SDL_RenderPresent(ren);
		}
    }
}
