#include "../inc/header.h"

bool is_restart;
int score;

void pause_game(SDL_Renderer *ren)
{
	SDL_Event event;
	int x = 0, y = 0;
	char sc_str[256];

	SDL_Texture *background = loadTexture("resource/images/pause/pause.png", ren);

	SDL_Texture *temp1 = loadTexture("resource/images/pause/resume_button.png", ren);
	//SDL_Texture *temp2 = loadTexture("resource/images/pause/restart_button.png", ren);
	SDL_Texture *temp3 = loadTexture("resource/images/pause/mainmenu_button.png", ren);
	SDL_Texture *pause = loadTexture("resource/images/pause/pause23.png", ren);
	SDL_Texture *score_tex = loadTexture("resource/images/pause/score.png", ren);

	SDL_Texture *resume = loadTexture("resource/images/pause/resume_button.png", ren);
	SDL_Texture *resume_pressed = loadTexture("resource/images/pause/resume_button_pressed.png", ren);
	SDL_Texture *resume_on = loadTexture("resource/images/pause/resume_button_on.png", ren);

	SDL_Texture *mainmenu = loadTexture("resource/images/pause/mainmenu_button.png", ren);
	SDL_Texture *mainmenu_pressed = loadTexture("resource/images/pause/mainmenu_button_pressed.png", ren);
	SDL_Texture *mainmenu_on = loadTexture("resource/images/pause/mainmenu_button_on.png", ren);

	while(SDL_PollEvent(&event)) 
	{
        if (event.type == SDL_QUIT)
       	{
       		IS_PAUSE = false;
       		RUN = false;
       		return;
       	}

       	if(event.type == SDL_MOUSEBUTTONDOWN)
        {
        	x = event.motion.x;
        	y = event.motion.y;
        	if((x > 264 && x < 534) && (y > 490 && y < 560))
        	{
        		//if(!IS_SOUND_OFF)Play_Sound(click);
        		SDL_RenderClear(ren);
        		renderTexture(background, ren, 0, 0, 800, 1000);
        		renderTexture(pause, ren, 280, 220, 224, 51);
        		renderTexture(score_tex, ren, 325, 330, 142, 30);
        		renderTexture(resume_pressed, ren, 264, 490, 270, 71);
        		renderTexture(mainmenu, ren, 264, 690, 270, 71);
        		SDL_RenderPresent(ren);
        		SDL_Delay(100);

        		SDL_RenderClear(ren);
        		renderTexture(background, ren, 0, 0, 800, 1000);
        		renderTexture(pause, ren, 280, 220, 224, 51);
        		renderTexture(score_tex, ren, 325, 330, 142, 30);
				sprintf(sc_str, "%i", score);
				SDL_Color color1 = { 255, 255, 255, 255 };
				renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color1, 25, ren_mainplane),ren_mainplane, 355, 380);
        		renderTexture(temp1, ren, 264, 490, 270, 71);
        		renderTexture(mainmenu, ren, 264, 690, 270, 71);
        		SDL_RenderPresent(ren);
        		SDL_Delay(100);

        		IS_PAUSE = false;
        		//cleanUp(music, click);
				return;
        	}

        	if((x > 264 && x < 534) && (y > 690 && y < 760))
        	{
        		//if(!IS_SOUND_OFF)Play_Sound(click);
        		SDL_RenderClear(ren);
        		renderTexture(background, ren, 0, 0, 800, 1000);
        		renderTexture(pause, ren, 280, 220, 224, 51);
        		renderTexture(score_tex, ren, 325, 330, 142, 30);
				sprintf(sc_str, "%i", score);
				SDL_Color color1 = { 255, 255, 255, 255 };
				renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color1, 25, ren_mainplane),ren_mainplane, 355, 380);
        		renderTexture(resume, ren, 264, 490, 270, 71);
        		renderTexture(mainmenu_pressed, ren, 264, 690, 270, 71);
        		SDL_RenderPresent(ren);
        		SDL_Delay(100);

        		SDL_RenderClear(ren);
        		renderTexture(background, ren, 0, 0, 800, 1000);
        		renderTexture(pause, ren, 280, 220, 224, 51);
        		renderTexture(score_tex, ren, 325, 330, 142, 30);
        		renderTexture(resume, ren, 264, 490, 270, 71);
        		renderTexture(temp3, ren, 264, 690, 270, 71);
        		SDL_RenderPresent(ren);
        		SDL_Delay(100);

        		IS_PAUSE = false;
        		IS_MENU = true;
        		//cleanUp(music, click);
        		return;
        	}
        }

        if(event.type == SDL_MOUSEMOTION)
        {
        	x = event.motion.x;
        	y = event.motion.y;
        	if((x > 264 && x < 534) && (y > 490 && y < 560))
        	{
        		resume = resume_on;
        	}
        	if((x > 264 && x < 534) && (y > 590 && y < 660))
        	{
        		//restart = restart_on;
        	}
        	if((x > 264 && x < 534) && (y > 690 && y < 760))
        	{
        		mainmenu = mainmenu_on;
        	}

        }

        SDL_RenderClear(ren);
        renderTexture(background, ren, 0, 0, 800, 1000);
        renderTexture(pause, ren, 280, 220, 224, 51);
        renderTexture(score_tex, ren, 325, 330, 142, 30);
		sprintf(sc_str, "%i", score);
		SDL_Color color1 = { 255, 255, 255, 255 };
		renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color1, 25, ren_mainplane),ren_mainplane, 355, 380);
        renderTexture(resume, ren, 264, 490, 270, 71);
        renderTexture(mainmenu, ren, 264, 690, 270, 71);
        SDL_RenderPresent(ren);
	}
	return;
}
