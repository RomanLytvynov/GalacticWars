#include "../inc/header.h"

SDL_Texture* LoadImage(const char * file, SDL_Renderer *renderer){
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = SDL_LoadBMP(file);
    
    if (loadedImage != NULL){
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else {
        printf("%s\n", SDL_GetError());
    }

    return texture;
}

SDL_Texture* loadTexture(const char *file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file);
	if (!texture)
	{
	    printf("%s\n",IMG_GetError()); // Можно заменить на SDL_GetError()
	}
	return texture;
}
