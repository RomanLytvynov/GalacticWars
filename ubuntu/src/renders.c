#include "../inc/header.h"

SDL_Renderer *ren_mainplane;
SDL_Texture *ex[5];
SDL_Texture *background;
SDL_Texture *temp_ex;
SDL_Texture *bullet;
SDL_Texture *main_ship_png;
SDL_Texture *main_ship_tex[12];

int sprite_i;

void render_boom(t_enemy **pack, Uint32 *timeout_anim_boom, int *counter_ren_boom) {
    if(SDL_TICKS_PASSED(SDL_GetTicks(), *timeout_anim_boom)) {
        switch((*counter_ren_boom) % 5) {
            case 0: 
                    temp_ex = ex[0];
                    break;
            case 1: 
                    temp_ex = ex[1];
                    break;
            case 2: 
                    temp_ex = ex[2];
                    break;
            case 3: 
                    temp_ex = ex[3];
                    break;
            case 4: 
                    (*pack)->is_boom = false;
                    temp_ex = ex[4];
                    break;
        }
        (*counter_ren_boom)++;
        
        (*timeout_anim_boom) = SDL_GetTicks()+ 70;
    }
    int size = get_size_pack(pack);
    renderTexture(temp_ex, ren_mainplane, (*pack)->x_enemy, (*pack)->y_enemy, size, size);
}

void render_enemy(t_enemy **pack, Uint32 *timeout_anim_enemy, unsigned int *counter_ren) {
    SDL_Texture **enemy_tex = get_enemy_tex(pack);
    SDL_Texture *enemy = enemy_tex[sprite_i];
    int size = get_size_pack(pack);

    if(SDL_TICKS_PASSED(SDL_GetTicks(), *timeout_anim_enemy)) {
    switch ((*counter_ren) % 3) {
        case 0:
                sprite_i = 0;
                enemy = enemy_tex[0];
                break;
        case 1:
                sprite_i = 1;
                enemy = enemy_tex[1];
                break;
        case 2:
                sprite_i = 2;
                enemy = enemy_tex[2];
                break;
    }

    (*timeout_anim_enemy) = SDL_GetTicks() + 250;
    
    }

    renderTexture(enemy, ren_mainplane, (*pack)->x_enemy, (*pack)->y_enemy, size, size);
}

void render_main_ship(Uint32 *timeout_anim, unsigned int *counter_ren) {
     if(SDL_TICKS_PASSED(SDL_GetTicks(), *timeout_anim)) {
            if (main_ship.left) {
                if((*counter_ren) % 3 == 0){
                    main_ship_png = main_ship_tex[4];
                }
                if((*counter_ren) % 3 == 1){
                    if (main_ship.hited) {
                        main_ship_png = main_ship_tex[7];
                    }
                    else {
                        main_ship_png = main_ship_tex[5];
                    }
                }
                if((*counter_ren) % 3 == 2){
                    main_ship_png = main_ship_tex[6];
                }
            }
            else if (main_ship.right) {
                if((*counter_ren) % 3 == 0){
                    main_ship_png = main_ship_tex[8];
                }
                if((*counter_ren) % 3 == 1){
                    if (main_ship.hited) {
                        main_ship_png = main_ship_tex[11];
                    }
                    else {
                        main_ship_png = main_ship_tex[9];
                    }
                }
                if((*counter_ren) % 3 == 2){
                    main_ship_png = main_ship_tex[10];
                }
            }
            else {
                if((*counter_ren) % 3 == 0){
                    main_ship_png = main_ship_tex[0];
                }
                if((*counter_ren) % 3 == 1){
                    if (main_ship.hited) {
                        main_ship_png = main_ship_tex[3];
                    }
                    else {
                        main_ship_png = main_ship_tex[1];
                    }
                }
                if((*counter_ren) % 3 == 2){
                    main_ship_png = main_ship_tex[2];
                }
            }
            (*counter_ren)++;
            (*timeout_anim) = SDL_GetTicks() + 250;
            }
            renderTexture(main_ship_png, ren_mainplane, main_ship.x, main_ship.y, 128, 128);
}
