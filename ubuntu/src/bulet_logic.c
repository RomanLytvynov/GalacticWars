#include "../inc/header.h"

t_ship main_ship;
Mix_Chunk *soundlist[8];
t_bullet **ammo;

unsigned int invince_fraim() {
    main_ship.hited = false;
    return 0;
}

unsigned int laser_off() {
    pack4->is_shoot = false;
    pack4->burst = false;
    return 0;
}

unsigned int laser_burst() {
    Mix_PlayChannel(-1, soundlist[5], 0);
    pack4->burst = true;
    SDL_AddTimer(2000, laser_off, NULL);
    return 0;
}

void spawn_bullet(int x,  int y, t_bullet **ammo, int *a, bool *reload, int *start_reload) {
    ammo[*a]->on_display = true;
    ammo[*a]->x = x + 54;
    ammo[*a]->y = y - 20;
    (*a)++;
    if (*a == 50) {
        *reload = true;
        *start_reload = SDL_GetTicks() ;
        *a = 0;
    }
}

void ship_ammo_fly(t_bullet **ammo, t_enemy ***pack, int i) {
    for (int k = 0; k < 4; k++) {
        int size;
        switch(k) {
            case 0:
            case 1: size = 96; break;
            case 2: size = 140; break;
            case 3: size = 300; break;
        }
        ammo[i]->y -= 8;
        for (int j = 0; pack[k][j]; j++) {
            if ( pack[k][j]->on_display 
            && (ammo[i]->y >= pack[k][j]->y_enemy && ammo[i]->y <= pack[k][j]->y_enemy + size) 
            && (ammo[i]->x >= pack[k][j]->x_enemy && ammo[i]->x <= pack[k][j]->x_enemy + size)) {
                ammo[i]->on_display = false;
                pack[k][j]->hp -= main_ship.damage;

                if (pack[k][j]->hp <= 0) {
                    switch(k) {
                        case 0:
                                score += 250;
                                break;
                        case 1:
                                score += 100;
                                break;
                        case 2:
                                score += 500;
                                break;
                        case 3: 
                                score += 1000;
                                break;
                    }
                    
                    pack[k][j]->is_boom = true;
                    pack[k][j]->on_display = false; 
                }
            }
        }
    }
}

void enemy_spawn_bullet(t_enemy *enemy) {
    if (enemy -> pack_num == 1) {
        enemy->en_bullet.x = enemy->x_enemy + 32;
        enemy->en_bullet.y = enemy->y_enemy + 64;
        enemy->en_bullet.on_display = true;
    }
    if (enemy -> pack_num == 3) {
        enemy->en_bullet.x = enemy->x_enemy + 70;
        enemy->en_bullet.y = enemy->y_enemy + 140;
        enemy->en_bullet.on_display = true;
    }
}

/*void enemy_spawn_laser(t_enemy *enemy, int i) {
    if (enemy -> pack_num == 4) {
        enemy->en_bullet.x = enemy->x_enemy + 32;
        enemy->en_bullet.y = enemy->y_enemy + 64 + i;
        enemy->en_bullet.on_display = true;
    }
}*/

void enemy_ammo_fly(t_enemy *enemy, int x, int y) {
    if(enemy -> pack_num == 1) {
        if (enemy->en_bullet.on_display) {
            for (int j = 0; j < 20; j++) {
            if(((enemy->en_bullet.x + j>= x + 48 &&  enemy->en_bullet.x + j <= x + 80)
            && (enemy->en_bullet.y  >= y && enemy->en_bullet.y <= y + 88)) 
            || ((enemy->en_bullet.x + j >= x &&  enemy->en_bullet.x+ j <= x + 128)
            && (enemy->en_bullet.y >= y + 88 && enemy->en_bullet.y <= y + 120))) {
                    if (main_ship.hited) {
                        enemy->en_bullet.y += 8;
                        return;
                    }
                    main_ship.hp--;
                    main_ship.hited = true;
                    SDL_AddTimer(2000, invince_fraim, NULL);
                    enemy->en_bullet.on_display =false;
                    return;
                }
            }
            for (int j = 0; j < 20; j++) {
                if((((enemy->en_bullet.x  >= x + 48 &&  enemy->en_bullet.x <= x + 80)
                && (enemy->en_bullet.y + j >= y && enemy->en_bullet.y + j <= y + 88)) 
                || ((enemy->en_bullet.x >= x &&  enemy->en_bullet.x <= x + 128)
                && (enemy->en_bullet.y + j >= y + 88 && enemy->en_bullet.y + j <= y + 120)))) {
                    if (main_ship.hited) {
                        enemy->en_bullet.y += 8;
                        return;
                    }
                    main_ship.hp--;
                    main_ship.hited = true;
                    SDL_AddTimer(2000, invince_fraim, NULL);
                    enemy->en_bullet.on_display =false;
                    return;
                }
            }
            enemy->en_bullet.y += 8;
            if (enemy->en_bullet.y > 1000) {
                enemy->en_bullet.on_display =false;
            }
        }
    }
    if(enemy -> pack_num == 3) {
        if (enemy->en_bullet.on_display) {
            for (int j = 0; j < 20; j++) {
            if(((enemy->en_bullet.x + j>= x + 48 &&  enemy->en_bullet.x + j <= x + 80)
            && (enemy->en_bullet.y  >= y && enemy->en_bullet.y <= y + 88)) 
            || ((enemy->en_bullet.x + j >= x &&  enemy->en_bullet.x+ j <= x + 128)
            && (enemy->en_bullet.y >= y + 88 && enemy->en_bullet.y <= y + 120))) {
                    if (main_ship.hited) {
                        enemy->en_bullet.y += 15;
                        return;
                    }
                    main_ship.hp--;
                    main_ship.hited = true;
                    SDL_AddTimer(2000, invince_fraim, NULL);
                    enemy->en_bullet.on_display =false;
                    return;
                }
            }
            for (int j = 0; j < 20; j++) {
                if((((enemy->en_bullet.x  >= x + 48 &&  enemy->en_bullet.x <= x + 80)
                && (enemy->en_bullet.y + j >= y && enemy->en_bullet.y + j <= y + 88)) 
                || ((enemy->en_bullet.x >= x &&  enemy->en_bullet.x <= x + 128)
                && (enemy->en_bullet.y + j >= y + 88 && enemy->en_bullet.y + j <= y + 120)))) {
                    if (main_ship.hited) {
                        enemy->en_bullet.y += 15;
                        return;
                    }
                    main_ship.hp--;
                    main_ship.hited = true;
                    SDL_AddTimer(2000, invince_fraim, NULL);
                    enemy->en_bullet.on_display =false;
                    return;
                }
            }
            enemy->en_bullet.y += 15;
            if (enemy->en_bullet.y > 1000) {
                enemy->en_bullet.on_display =false;
            }
        }
    }
}

void laser_cast(t_enemy *enemy) {
    enemy->is_shoot = true;
    Mix_PlayChannel(-1, soundlist[7], 0);
        SDL_AddTimer(1500, laser_burst, NULL);
}
