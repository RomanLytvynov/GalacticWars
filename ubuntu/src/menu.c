#include "../inc/header.h"

int h_score;

bool init_m() {
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        return false;
    }
    return true;
}

void cleanUp(Mix_Music *music, Mix_Chunk *click) {
	Mix_HaltMusic();
	Mix_FreeChunk( click );
    Mix_FreeMusic( music );
    Mix_CloseAudio();
}

void Play_Sound(Mix_Chunk *click) {
	if( Mix_PlayChannel(-1, click, 0 ) == -1 ) {
    	printf("PlayVoice error\n");
        return;    
    }
}

void menu(bool *is_menu, SDL_Renderer *ren) {

	SDL_Event event;
	int x = 0, y = 0;

	SDL_Texture *background = loadTexture("resource/images/menu/title.png", ren);
	SDL_Texture *temp1 = loadTexture("resource/images/menu/button_start.png", ren);
	SDL_Texture *temp2 = loadTexture("resource/images/menu/exit_button.png", ren);

	SDL_Texture *start = loadTexture("resource/images/menu/button_start.png", ren);
	SDL_Texture *start_pressed = loadTexture("resource/images/menu/button_start_pressed.png", ren);
	SDL_Texture *start_on = loadTexture("resource/images/menu/button_start_on.png", ren);

	SDL_Texture *exit = loadTexture("resource/images/menu/exit_button.png", ren);
	SDL_Texture *exit_pressed = loadTexture("resource/images/menu/exit_button_pressed.png", ren);
	SDL_Texture *exit_on = loadTexture("resource/images/menu/exit_button_on.png", ren);

	SDL_Texture *sound_on = loadTexture("resource/images/menu/button_sound_on.png", ren);
	SDL_Texture *sound_off = loadTexture("resource/images/menu/button_sound_off.png", ren);
	SDL_Texture *music_on = loadTexture("resource/images/menu/button_music_on.png", ren);
	SDL_Texture *music_off = loadTexture("resource/images/menu/button_music_off.png", ren);

	if(!init_m()) printf("Without music\n");
	Mix_Music *music = Mix_LoadMUS( "resource/audio/ost/1.mp3" );
	Mix_Chunk *click = Mix_LoadWAV( "resource/audio/sounds/click_1.wav" );
	Mix_VolumeMusic(30);
	while (IS_MENU) {
		while (SDL_PollEvent(&event)) 
		{

			if (event.type == SDL_QUIT) {
				*is_menu = false;
				RUN = false;
				cleanUp(music, click);
				return;
			}

			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				x = event.motion.x;
				y = event.motion.y;
				if((x > 250 && x < 550) && (y > 700 && y < 780))
				{
					if(!IS_SOUND_OFF)Play_Sound(click);
					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(start_pressed, ren, 250, 700, 299, 79);
					renderTexture(exit, ren, 250, 800, 299, 79);
					if(!IS_SOUND_OFF) renderTexture(sound_on, ren, 300, 900, 84, 62);
					else renderTexture(sound_off, ren, 300, 900, 84, 62);
					if(!IS_MUSIC_OFF) renderTexture(music_on, ren, 415, 900, 84, 62);
					else renderTexture(music_off, ren, 415, 900, 84, 62);
					SDL_RenderPresent(ren);
					SDL_Delay(100);

					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(temp1, ren, 250, 700, 299, 79);
					renderTexture(exit, ren, 250, 800, 299, 79);
					if(!IS_SOUND_OFF) renderTexture(sound_on, ren, 300, 900, 84, 62);
					else renderTexture(sound_off, ren, 300, 900, 84, 62);
					if(!IS_MUSIC_OFF) renderTexture(music_on, ren, 415, 900, 84, 62);
					else renderTexture(music_off, ren, 415, 900, 84, 62);
					SDL_RenderPresent(ren);
					SDL_Delay(100);
					*is_menu = false;
					cleanUp(music, click);
					return;
				}

				if((x > 250 && x < 550) && (y > 800 && y < 880))
				{
					if(!IS_SOUND_OFF)Play_Sound(click);
					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(exit_pressed, ren, 250, 800, 299, 79);
					renderTexture(start, ren, 250, 700, 299, 79);
					if(!IS_SOUND_OFF) renderTexture(sound_on, ren, 300, 900, 84, 62);
					else renderTexture(sound_off, ren, 300, 900, 84, 62);
					if(!IS_MUSIC_OFF) renderTexture(music_on, ren, 415, 900, 84, 62);
					else renderTexture(music_off, ren, 415, 900, 84, 62);
					SDL_RenderPresent(ren);
					SDL_Delay(100);

					SDL_RenderClear(ren);
					renderTexture(background, ren, 0, 0, 800, 1000);
					renderTexture(temp2, ren, 250, 800, 299, 79);
					renderTexture(start, ren, 250, 700, 299, 79);
					if(!IS_SOUND_OFF) renderTexture(sound_on, ren, 300, 900, 84, 62);
					else renderTexture(sound_off, ren, 300, 900, 84, 62);
					if(!IS_MUSIC_OFF) renderTexture(music_on, ren, 415, 900, 84, 62);
					else renderTexture(music_off, ren, 415, 900, 84, 62);
					SDL_RenderPresent(ren);
					SDL_Delay(100);
					*is_menu = false;
					RUN = false;
					cleanUp(music, click);
					return;
				}

				if((x > 300 && x < 384)&&(y > 900 && y < 962))
				{
					if(!IS_SOUND_OFF) IS_SOUND_OFF = true;
					else IS_SOUND_OFF = false;
				}
				if((x > 415 && x < 499)&&(y > 900 && y < 962))
				{
					if(!IS_MUSIC_OFF) 
					{
						IS_MUSIC_OFF = true;
					}
					else IS_MUSIC_OFF = false;
				}


			}

			if(event.type == SDL_MOUSEMOTION)
			{
				x = event.motion.x;
				y = event.motion.y;
				if((x > 250 && x < 550) && (y > 700 && y < 780))
				{
					start = start_on;
				}
				if((x > 250 && x < 550) && (y > 800 && y < 880))
				{
					exit = exit_on;
				}

			}
			if(!IS_MUSIC_OFF)
			{
				if( Mix_PlayingMusic() == 0 )
				{
					if( Mix_PlayMusic( music, -1 ) == -1 )
					{
						return;
					}    
				}
			}
			else Mix_HaltMusic();

			SDL_RenderClear(ren);
			renderTexture(background, ren, 0, 0, 800, 1000);
			char h_score_str[256];
			sprintf(h_score_str, "%i", h_score);
			SDL_Color color1 = { 255, 255, 255, 255 };
			renderTextureWithout(renderText(h_score_str, "resource/text/ttf/PressStart2P-Regular.ttf", color1, 25, ren_mainplane),ren_mainplane, 355, 500);
			renderTexture(start, ren, 250, 700, 299, 79);
			renderTexture(exit, ren, 250, 800, 299, 79);
			if(!IS_SOUND_OFF) renderTexture(sound_on, ren, 300, 900, 84, 62);
			else renderTexture(sound_off, ren, 300, 900, 84, 62);
			if(!IS_MUSIC_OFF) renderTexture(music_on, ren, 415, 900, 84, 62);
			else renderTexture(music_off, ren, 415, 900, 84, 62);
			SDL_RenderPresent(ren);
		}
	}

	return;

}

