#include "../inc/header.h"

int get_size_pack(t_enemy **pack) {
    switch((*pack)->pack_num) {
        case 1:
        case 2:
            return 96;
        case 3:
            return 140;
        case 4:
            return 400;
    }
    return 0;
}

SDL_Texture **get_enemy_tex(t_enemy **pack) {
    switch((*pack)->pack_num) {
        case 1:
            return enemy1;
        case 2:
            return enemy2;
        case 3:
            return enemy3;
        case 4:
            return enemy4;
    }
    return NULL;
}
