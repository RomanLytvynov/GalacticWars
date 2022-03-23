#include "../inc/header.h"

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
   SDL_Rect pos;
   pos.x = x;
   pos.y = y;
   SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
   SDL_RenderCopy(rend, tex, NULL, &pos);
}
