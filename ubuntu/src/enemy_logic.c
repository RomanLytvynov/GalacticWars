#include "../inc/header.h"

t_enemy **pack;
int score;
int count_packs;
Mix_Chunk *soundlist[8];
Uint32 timeout_shoot = 0;
Uint32 timeout_fly = 1000;

bool packs_on_display[4];

unsigned int mv_pack1_timer() {
    for (int i = 0; pack1[i]; i++) {
        pack1[i] -> y_enemy += 6;
    }
    return 0;
}

void mv_pack1(t_enemy **pack1, int x, int y, bool *on_display) {
    pack = pack1;
    if (pack1[0]->y_enemy < 800 / 5 - 64) {
            for (int i = 0; pack1[i]; i++) {
                if (pack1[i] -> on_display) {
                    pack1[i] -> y_enemy += 2;
                }
            }
    }
    else {
        for (int i = 0; i < 3; i++)
        if (pack1[i] -> on_display && pack1[0] -> on_display){
            if (!pack1[i]->en_bullet.on_display){ 
                enemy_spawn_bullet(pack1[i]);
                Mix_PlayChannel(-1, soundlist[6], 0);
                timeout_fly = SDL_GetTicks() + 1000;
            }
        }
    } 
    if (!pack1[0] -> on_display) {
        if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout_fly))
            for (int i = 0; pack1[i]; i++) {
            pack1[i] -> y_enemy += 6;
        }
    }

    bool temp_on_display = false;    
    for (int i = 0; i < 3; i++) {
        if (pack1[i]->y_enemy < 1000) {
            temp_on_display = true;
        }
    }    
    *on_display = temp_on_display;
    packs_on_display[0] = temp_on_display;

    for (int i = 0; pack1[i]; i++) {
        for (int j = 0; j < 64; j++) {
            if((((pack1[i] -> x_enemy + j  >= x + 48 &&  pack1[i] -> x_enemy + j <= x + 80)
            && (pack1[i] -> y_enemy  >= y && pack1[i] -> y_enemy <= y + 88)) 
            || ((pack1[i] -> x_enemy + j >= x &&  pack1[i] -> x_enemy + j <= x + 128)
            && (pack1[i] -> y_enemy >= y + 88 && pack1[i] -> y_enemy <= y + 120)))
            && pack1[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack1[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }
        for (int j = 0; j < 64; j++) {
            if((((pack1[i] -> x_enemy  >= x + 48 &&  pack1[i] -> x_enemy <= x + 80)
            && (pack1[i] -> y_enemy + j >= y && pack1[i] -> y_enemy + j <= y + 88)) 
            || ((pack1[i] -> x_enemy >= x &&  pack1[i] -> x_enemy <= x + 128)
            && (pack1[i] -> y_enemy + j >= y + 88 && pack1[i] -> y_enemy + j <= y + 120)))
            && pack1[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack1[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }

    }
}

void mv_pack2(t_enemy **pack2, int x, int y, bool *on_display) {
    for (int i = 0; pack2[i]; i++) {
        pack2[i] -> y_enemy += 8;
    }
    
    bool temp_on_display = false;    
    for (int i = 0; i < 4; i++) {
        if (pack2[i]->y_enemy < 1000) {
            temp_on_display = true;
        }
    }    
    *on_display = temp_on_display;
    packs_on_display[1] = temp_on_display;
    
    for (int i = 0; pack2[i]; i++) {
        for (int j = 0; j < 64; j++) {
            if((((pack2[i] -> x_enemy + j  >= x + 48 &&  pack2[i] -> x_enemy + j <= x + 80)
            && (pack2[i] -> y_enemy + 20  >= y && pack2[i] -> y_enemy <= y + 88)) 
            || ((pack2[i] -> x_enemy + j >= x &&  pack2[i] -> x_enemy + j <= x + 128)
            && (pack2[i] -> y_enemy + 20 >= y + 88 && pack2[i] -> y_enemy <= y + 120)))
            && pack2[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack2[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }
        for (int j = 0; j < 64; j++) {
            if((((pack2[i] -> x_enemy  >= x + 48 &&  pack2[i] -> x_enemy <= x + 80)
            && (pack2[i] -> y_enemy + 20 + j >= y && pack2[i] -> y_enemy + j <= y + 88)) 
            || ((pack2[i] -> x_enemy >= x &&  pack2[i] -> x_enemy <= x + 128)
            && (pack2[i] -> y_enemy + 20 + j >= y + 88 && pack2[i] -> y_enemy + j <= y + 120)))
            && pack2[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack2[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }

    }
}

void mv_pack3(t_enemy **pack3, int x, int y, bool *on_display) {
    
    if (pack3[0] -> y_enemy <= 300) {
        pack3[0] -> y_enemy += 12;
    }
    if (pack3[1] -> y_enemy <= 200 && pack3[0] -> y_enemy >= 0) {
        pack3[1] -> y_enemy += 12;
    }
    if (pack3[2] -> y_enemy <= 100 && pack3[1] -> y_enemy >= 0) {
        pack3[2] -> y_enemy += 12;
    }

    if (!pack3[0] -> is_shoot && pack3[2] -> y_enemy > 100 && !pack3[1] -> is_shoot && pack3[0] ->on_display) {
        pack3[0] -> is_shoot = true;
        Mix_PlayChannel(-1, soundlist[6], 0);
        enemy_spawn_bullet(pack3[0]);
        timeout_shoot = SDL_GetTicks() + 500;
    }

    if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout_shoot) && pack3[0] -> is_shoot && pack3[1] ->on_display) {
        pack3[1] -> is_shoot = true;
        pack3[0] -> is_shoot = false;
        Mix_PlayChannel(-1, soundlist[6], 0);
        enemy_spawn_bullet(pack3[1]);
        timeout_shoot = SDL_GetTicks() + 500;
    }

    if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout_shoot) && pack3[1] -> is_shoot && pack3[2] ->on_display) {
        pack3[2] -> is_shoot = true;
        pack3[1] -> is_shoot = false;
        Mix_PlayChannel(-1, soundlist[6], 0);
        enemy_spawn_bullet(pack3[2]);
        timeout_shoot = SDL_GetTicks() + 500;
    }

    bool temp_on_display = false;    
    for (int i = 0; i < 3; i++) {
        if (pack3[i]->y_enemy < 1000 || pack3[i] -> on_display) {
            temp_on_display = true;
        }
    }    
    *on_display = temp_on_display;
    packs_on_display[2] = temp_on_display;

    for (int i = 0; pack3[i]; i++) {    
        for (int j = 0; j < 120; j++) {
            if((((pack3[i] -> x_enemy + j  >= x + 48 &&  pack3[i] -> x_enemy + j <= x + 80)
            && (pack3[i] -> y_enemy + j  >= y && pack3[i] -> y_enemy + j <= y + 88)) 
            || ((pack3[i] -> x_enemy + j >= x &&  pack3[i] -> x_enemy + j <= x + 128)
            && (pack3[i] -> y_enemy + j >= y + 88 && pack3[i] -> y_enemy + j <= y + 120)))
            && pack3[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack3[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }
        for (int j = 0; j < 120; j++) {
            if((((pack3[i] -> x_enemy  >= x + 48 &&  pack3[i] -> x_enemy <= x + 80)
            && (pack3[i] -> y_enemy + j >= y && pack3[i] -> y_enemy + j <= y + 88)) 
            || ((pack3[i] -> x_enemy >= x &&  pack3[i] -> x_enemy <= x + 128)
            && (pack3[i] -> y_enemy + j >= y + 88 && pack3[i] -> y_enemy + j <= y + 120)))
            && pack3[i] -> on_display) {
                if (main_ship.hited) {
                    return;
                }
                pack3[i]->on_display = false;
                Mix_PlayChannel(-1, soundlist[3], 0);
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
            }
        }

    }


}

void mv_pack4(t_enemy *pack4, int x, int y, bool *on_display) {

    if (pack4 -> y_enemy <= 50) {
        pack4 -> y_enemy += 2;
    }
    else if (pack4->on_display && !pack4->is_shoot) {
        laser_cast(pack4);
    }
    bool temp_on_display = false;    
    if (pack4->y_enemy < 1000 || pack4 -> on_display) {
        temp_on_display = true;
    }    
    *on_display = temp_on_display;
    packs_on_display[3] = temp_on_display;
        
    for (int j = 0; j < 300; j++) {
        if((((pack4 -> x_enemy + j  >= x + 48 &&  pack4 -> x_enemy + j <= x + 80)
        && (pack4 -> y_enemy + j  >= y && pack4 -> y_enemy + j <= y + 88)) 
        || ((pack4 -> x_enemy + j >= x &&  pack4 -> x_enemy + j <= x + 128)
        && (pack4 -> y_enemy + j >= y + 88 && pack4 -> y_enemy + j <= y + 120)))
        && pack4 -> on_display) {
            if (main_ship.hited) {
                return;
            }
            pack4->on_display = false;
            Mix_PlayChannel(-1, soundlist[3], 0);
            IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
        }
    }
    for (int j = 0; j < 300; j++) {
        if((((pack4 -> x_enemy  >= x + 48 &&  pack4 -> x_enemy <= x + 80)
        && (pack4 -> y_enemy + j >= y && pack4 -> y_enemy + j <= y + 88)) 
        || ((pack4 -> x_enemy >= x &&  pack4 -> x_enemy <= x + 128)
        && (pack4 -> y_enemy + j >= y + 88 && pack4 -> y_enemy + j <= y + 120)))
        && pack4 -> on_display) {
            if (main_ship.hited) {
                return;
            }
            pack4->on_display = false;
            Mix_PlayChannel(-1, soundlist[3], 0);
            IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }
        }
    }

    
}

void mv_pack(t_enemy ***packs, int x, int y, bool *on_display) {
    for (int i = 0; i < count_packs; i++) {
        switch(packs[i][0]->pack_num) {
            case 1:
                mv_pack1(packs[i], x, y, on_display);
                break;
            case 2:
                mv_pack2(packs[i], x, y, on_display);
                break;
            case 3:
                mv_pack3(packs[i], x, y, on_display);
                break;
            case 4:
                mv_pack4(*packs[i], x, y, on_display);
                break;
        }
    }
}
