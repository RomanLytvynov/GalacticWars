#include "../inc/header.h"

t_enemy **pack1;
t_enemy **pack2;
t_enemy **pack3;
t_enemy *pack4;

Uint32 pack_timeout;

void init_pack1(void) {
    srand(time(NULL));
    int d_x = rand() % (100) - 50;
    if(main_ship.x <= 64) {
        pack1[0]->x_enemy = main_ship.x + 64;
        pack1[0]->y_enemy = -64;
    }
    else if (main_ship.x >= 650) {
        pack1[0]->x_enemy = main_ship.x - 10;
        pack1[0]->y_enemy = -64;
    }
    else {
        pack1[0]->x_enemy = main_ship.x + d_x;
        pack1[0]->y_enemy = -64;
    }

    pack1[1]->x_enemy = pack1[0]->x_enemy + 64;
    pack1[1]->y_enemy = pack1[0]->y_enemy - 64;
    
    pack1[2]->x_enemy = pack1[0]->x_enemy - 64;
    pack1[2]->y_enemy = pack1[0]->y_enemy - 64;
    
    pack1[0]->hp = 4 + score / 5000;
    pack1[0]->on_display = true;
    pack1[0]->en_bullet.on_display = false;
    pack1[0]->pack_num = 1;

    for (int i = 1; i < 3; i++) {
        pack1[i]->hp = 2 + score / 5000;
        pack1[i]->on_display = true;
        pack1[i]->en_bullet.on_display = false;
        pack1[i]->pack_num = 1;
    }

    pack_timeout = SDL_GetTicks() + 5000;
}

void init_pack2(void) {
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        pack2[i] -> x_enemy = rand() % 600 + 100;
        pack2[i] -> y_enemy = rand() %(-620) - 700;
        pack2[i] -> hp = 1 + score / 10000;        
        pack2[i]->on_display = true;
        pack2[i]->en_bullet.on_display = false;
        pack2[i]->pack_num = 2;

        for (int k = 0; k < i; k++) {
            for (int j = 0; j < 64; j++) {
                while((((pack2[i] -> x_enemy + j  >= pack2[k] -> x_enemy &&  pack2[i] -> x_enemy + j <= pack2[k] -> x_enemy +64)
                && (pack2[i] -> y_enemy  >= pack2[k] -> y_enemy && pack2[i] -> y_enemy <= pack2[k] -> y_enemy + 64)))
                && pack2[i] -> on_display) {
                    pack2[i] -> x_enemy = rand() % 600 + 100;
                    pack2[i] -> y_enemy = rand() %(-620) - 700;
                }
            }
        } 
    }

    pack_timeout = SDL_GetTicks() + 2000;
}

void init_pack3(void){
    for (int i = 0; i < 3; i++) {
        pack3[i] -> x_enemy = i*300 + 30;
        pack3[i] -> y_enemy = -400;
        pack3[i] -> hp = 4 + score / 10000;        
        pack3[i] -> on_display = true;
        pack3[i] -> pack_num = 3;
    }

    pack_timeout = SDL_GetTicks() + 5000;
}

void init_pack4(void){
    srand(time(NULL));
    int d_x = rand() % (100) - 50;
    if(main_ship.x <= 64) {
        pack4->x_enemy = main_ship.x + 64;
        pack4->y_enemy = -64;
    }
    else if (main_ship.x >= 650) {
        pack4->x_enemy = main_ship.x - 10;
        pack4->y_enemy = -64;
    }
    else {
        pack4->x_enemy = main_ship.x + d_x;
        pack4->y_enemy = -64;
    }
    pack4 -> hp = 10 + score / 15000;       
    pack4 -> on_display = true;
    pack4 -> pack_num = 4;

    pack_timeout = SDL_GetTicks() + 7000;
}

unsigned int init_pack() {
    srand(time(NULL));
        init_pack1();

    return 0;
}
