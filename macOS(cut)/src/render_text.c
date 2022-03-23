#include "../inc/header.h"


SDL_Texture* renderText(const char *message, const char *font_file, SDL_Color color, int font_size, SDL_Renderer *renderer) {  
        TTF_Font *font = TTF_OpenFont(font_file, font_size);
        if (font == NULL){
                printf("TTF_OpenFont\n");
                return NULL;
        }
        
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(font, message, color));
        if (texture == NULL){
                printf("CreateTexture\n"); 
        }
        TTF_CloseFont(font);
        return texture;
}
