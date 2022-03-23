#include "../inc/header.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;

bool IS_MENU = true;
bool RUN = true;
bool IS_SOUND_OFF = false;
bool IS_MUSIC_OFF = false;
bool IS_PAUSE = false;
bool is_restart = false;
bool IS_GAME_OVER = false;
bool kostyl = true;
SDL_Window *win = NULL;

unsigned int time_sec = 0;
unsigned int counter_ren = 0;
double back[2] = {-5100 + SCREEN_HEIGHT, -10200 +  SCREEN_HEIGHT};
bool pack_on_display;

t_enemy **pack1;
t_enemy **pack2;
t_enemy **pack3;
t_enemy *pack4;

SDL_Renderer *ren_mainplane;
SDL_Texture *background;
SDL_Texture *ex[5];
SDL_Texture *temp_ex;
SDL_Texture *bullet;

SDL_Texture *enemy1[3];
SDL_Texture *enemy2[3];
SDL_Texture *enemy3[3];
SDL_Texture *enemy4[3];

SDL_Texture *main_ship_tex[12];

t_bullet **ammo;

int score = 0;
Uint32 pack_timeout = 2000;

const int playlist_size = 10;
const int soundlist_size = 7;
Mix_Music *playlist[10];
Mix_Chunk *soundlist[7];

int init() {
    pack_on_display = false;

    ammo = (t_bullet **)malloc(50*sizeof(t_bullet *));
    for (int i = 0; i < 50; i++) {
        ammo[i] = (t_bullet *)malloc(sizeof(t_bullet));
    }

    pack1 = (t_enemy **)malloc(3*sizeof(t_enemy *));
    for (int i = 0; i < 3; i++) {
        pack1[i] = (t_enemy *)malloc(sizeof(t_enemy));
    }   
    

    pack2 = (t_enemy **)malloc(4*sizeof(t_enemy *));
    for (int i = 0; i < 4; i++) {
        pack2[i] = (t_enemy *)malloc(sizeof(t_enemy *));
    }
    

    pack3 = (t_enemy **)malloc(3*sizeof(t_enemy *));
    for (int i = 0; i < 3; i++) {
        pack3[i] = (t_enemy *)malloc(sizeof(t_enemy *));
    }
    

    pack4 = (t_enemy *)malloc(sizeof(t_enemy));


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error1\n");
        return 1;
    }

    if (TTF_Init() != 0){
        printf("TTF_Init\n");
        SDL_Quit();
        return 1;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    else {
        Mix_Volume(2, 80);
        Mix_Volume(-1, 40);
    }

    return 0;
}

int quit() {
    
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

int main () 
{
    int file = open("resource/text/high_score.txt", O_RDONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    char h_score[256];
    char buff;
    int i = 0;
    while(read(file , &buff, 1)) {
        h_score[i] = buff;
    }
    close(file);

    if (init() == 1) {
        return 1;    
    }
    win = SDL_CreateWindow("GALACTIC WARS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (win == NULL) {
        printf("Error2\n");

        return 1;
    }

    main_ship.damage = 1 + score / 1000;

    ren_mainplane = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    main_ship_tex[0] = loadTexture("resource/images/main_ship/static/1.png", ren_mainplane);
    main_ship_tex[1] = loadTexture("resource/images/main_ship/static/2.png", ren_mainplane);
    main_ship_tex[2] = loadTexture("resource/images/main_ship/static/3.png", ren_mainplane);
    main_ship_tex[3] = loadTexture("resource/images/main_ship/static/4.png", ren_mainplane);
    main_ship_tex[4] = loadTexture("resource/images/main_ship/left/1.png", ren_mainplane);
    main_ship_tex[5] = loadTexture("resource/images/main_ship/left/2.png", ren_mainplane);
    main_ship_tex[6] = loadTexture("resource/images/main_ship/left/3.png", ren_mainplane);
    main_ship_tex[7] = loadTexture("resource/images/main_ship/left/4.png", ren_mainplane);
    main_ship_tex[8] = loadTexture("resource/images/main_ship/right/1.png", ren_mainplane);
    main_ship_tex[9] = loadTexture("resource/images/main_ship/right/2.png", ren_mainplane);
    main_ship_tex[10] = loadTexture("resource/images/main_ship/right/3.png", ren_mainplane);
    main_ship_tex[11] = loadTexture("resource/images/main_ship/right/4.png", ren_mainplane);

    ex[0] = loadTexture("resource/images/explosion/1.png", ren_mainplane);
    ex[1] = loadTexture("resource/images/explosion/2.png", ren_mainplane);
    ex[2] = loadTexture("resource/images/explosion/3.png", ren_mainplane);
    ex[3] = loadTexture("resource/images/explosion/4.png", ren_mainplane);
    ex[4] = loadTexture("resource/images/explosion/5.png", ren_mainplane);
    temp_ex = ex[0];

    enemy1[0] = loadTexture("resource/images/pack1/1.png", ren_mainplane);
    enemy1[1] = loadTexture("resource/images/pack1/2.png", ren_mainplane);
    enemy1[2] = loadTexture("resource/images/pack1/3.png", ren_mainplane);

    enemy2[0] = loadTexture("resource/images/pack2/1.png", ren_mainplane);
    enemy2[1] = loadTexture("resource/images/pack2/2.png", ren_mainplane);
    enemy2[2] = loadTexture("resource/images/pack2/3.png", ren_mainplane);

    enemy3[0] = loadTexture("resource/images/pack3/1.png", ren_mainplane);
    enemy3[1] = loadTexture("resource/images/pack3/2.png", ren_mainplane);
    enemy3[2] = loadTexture("resource/images/pack3/3.png", ren_mainplane);

    enemy4[0] = loadTexture("resource/images/pack4/1.png", ren_mainplane);
    enemy4[1] = loadTexture("resource/images/pack4/2.png", ren_mainplane);
    enemy4[2] = loadTexture("resource/images/pack4/3.png", ren_mainplane);

    background = loadTexture("resource/images/Field_scrolling.png", ren_mainplane);
    bullet = loadTexture("resource/images/bullet.png", ren_mainplane);
    SDL_Texture *bullet1 = loadTexture("resource/images/ammo/1.png", ren_mainplane);
    SDL_Texture *bullet2 = loadTexture("resource/images/ammo/2.png", ren_mainplane);
    SDL_Texture *bullet3 = loadTexture("resource/images/ammo/3.png", ren_mainplane);
    SDL_Texture *bullet_png = bullet1;

    SDL_Texture *health_bar[6];
    health_bar[0] = loadTexture("resource/images/interface/healthbar0.png", ren_mainplane);
    health_bar[1] = loadTexture("resource/images/interface/healthbar1.png", ren_mainplane);
    health_bar[2] = loadTexture("resource/images/interface/healthbar2.png", ren_mainplane);
    health_bar[3] = loadTexture("resource/images/interface/healthbar3.png", ren_mainplane);
    health_bar[4] = loadTexture("resource/images/interface/healthbar4.png", ren_mainplane);
    health_bar[5] = loadTexture("resource/images/interface/healthbar full.png", ren_mainplane);
    SDL_Texture *hp_current = health_bar[5];

    SDL_Texture *ammo_icon = loadTexture("resource/images/interface/ammo icon.png", ren_mainplane);

    SDL_Texture *reload_tex[8];
    reload_tex[0] = loadTexture("resource/images/interface/reload/1.png", ren_mainplane);
    reload_tex[1] = loadTexture("resource/images/interface/reload/2.png", ren_mainplane);
    reload_tex[2] = loadTexture("resource/images/interface/reload/3.png", ren_mainplane);
    reload_tex[3] = loadTexture("resource/images/interface/reload/4.png", ren_mainplane);
    reload_tex[4] = loadTexture("resource/images/interface/reload/5.png", ren_mainplane);
    reload_tex[5] = loadTexture("resource/images/interface/reload/6.png", ren_mainplane);
    reload_tex[6] = loadTexture("resource/images/interface/reload/7.png", ren_mainplane);
    reload_tex[7] = loadTexture("resource/images/interface/reload/8.png", ren_mainplane);
    SDL_Texture *reload_current = reload_tex[0];
    int sprait_reload_i = 0;
    bool run = true;
    SDL_Event e;

    int playlist_song_counter = 0;

    int x = 400 - 64;
    int y = 800;

    main_ship.x = x;
    main_ship.y = y;
    main_ship.hp = 5;
    main_ship.damage = 1;
    
    
    int ammo_count = 0;
    int counter_ren_boom = 5;
    int counter_ren_bullet = 0;

    int start_reload;
    bool reload = false;
    Uint32 timeout = 0;
    Uint32 timeout_anim_ship = 0;
    Uint32 timeout_anim_enemy1 = 0;
    Uint32 timeout_anim_enemy2 = 0;
    Uint32 timeout_anim_enemy3 = 0;
    Uint32 timeout_anim_enemy4 = 0;
    pack_timeout = 2000;
    Uint32 timeout_timer = 0;
    Uint32 timeout_anim_boom = 0;
    Uint32 timeout_reload = 0;
    Uint32 timeout_bullet = 0;

    t_enemy ***packs = (t_enemy ***)malloc(4*sizeof(t_enemy **));
    packs[0] = pack1;
    packs[1] = pack2;
    packs[2] = pack3;
    packs[3] = &pack4;

    count_packs = 4;

    char sc_str[256];
    char ammo_str[3];

    if (!Load_music(playlist_size, playlist)) {
        printf("Error!");
        return -1;
    }

    if (!load_sounds(soundlist_size, soundlist)) {
        printf("Error!");
        return -1;
    }

    while (run) {
        if( Mix_PlayingMusic() == 0 ) {
            if(playlist[playlist_song_counter] == NULL) {
                continue;
            }
            Mix_PlayMusic( playlist[playlist_song_counter], 1 );
            playlist_song_counter++;

            if (playlist_song_counter == playlist_size) {
                playlist_song_counter = 1;
            }
        }

        while(IS_MENU) {
            menu(&IS_MENU, ren_mainplane);//h_score);
        }
        if(RUN == false) {
            SDL_Delay(400);
            break;
        }

        doInput();
        if (SDL_GetTicks() - start_reload >= 3000) {
            reload = false;
        }

        if (e.type == SDL_QUIT) {
            run = false;
        }

        while (IS_PAUSE) {
            pause_game(ren_mainplane);
        }

        if (main_ship.up && y - 8 > SCREEN_HEIGHT / 5) {
            y -= 8;
        }
        if (main_ship.down  && y + 8 + 128 < SCREEN_HEIGHT) {
            y += 8;
        }
        if (main_ship.left && x - 12 > 0) {
            x -= 12;
        }
        if (main_ship.right  && x + 12 + 128 < SCREEN_WIDTH) {
            x += 12;
        }

        main_ship.x = x;
        main_ship.y = y;

        if (main_ship.shoot && !reload ) {
            if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
                spawn_bullet(x, y, ammo, &ammo_count, &reload, &start_reload);
                Mix_PlayChannel(-1, soundlist[4], 0);
                timeout = SDL_GetTicks() + 250;
            }
        }
    
        if (SDL_TICKS_PASSED(SDL_GetTicks(), pack_timeout)) {
            init_pack();
            pack_on_display = true;
            pack_timeout = SDL_GetTicks() + 7000;
        }

        SDL_RenderClear(ren_mainplane);
    
        renderTexture(background, ren_mainplane, 0, back[0], SCREEN_WIDTH, 5100);
        renderTexture(background, ren_mainplane, 0, back[1], SCREEN_WIDTH, 5100);
        
        render_main_ship(&timeout_anim_ship, &counter_ren);

            for (int i = 0; i < 50; i++) {
                if(ammo[i] -> on_display) {
                    if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout_bullet)) {
                        switch((counter_ren_bullet) % 3) {
                            case 0: 
                                    bullet_png = bullet1;
                                    break;
                            case 1: 
                                    bullet_png = bullet2;
                                    break;
                            case 2: 
                                    bullet_png = bullet3;
                                    break;
                        }
                        (counter_ren_bullet)++;
                        (timeout_bullet) = SDL_GetTicks()+ 500;
                    }
                    renderTexture(bullet_png, ren_mainplane, ammo[i]->x, ammo[i]->y, 20, 40);
                    ship_ammo_fly(ammo, packs, i);
                }
            }

            for (int i = 0; i < 3; i++) {
                if (pack1[i]->en_bullet.on_display) {
                        renderTexture(bullet, ren_mainplane, pack1[i]->en_bullet.x, pack1[i]->en_bullet.y, 20, 20);
                        enemy_ammo_fly(pack1[i], main_ship.x, main_ship.y);
                }
                if (pack1[i]->on_display) {
                    render_enemy(&pack1[i], &timeout_anim_enemy1, &counter_ren);
                }
                else if(pack1[i]->is_boom) {
                    Mix_PlayChannel(-1, soundlist[2], 0);
                    render_boom(&pack1[i], &timeout_anim_boom, &counter_ren_boom);
                    if (temp_ex == ex[4]) {
                        counter_ren_boom = 5;
                        continue;
                    }
                }

            }

            for (int i = 0; i < 4; i++) {
                if (pack2[i]->on_display) {
                    render_enemy(&pack2[i], &timeout_anim_enemy2, &counter_ren);
                }
                else if(pack2[i]->is_boom) {
                    Mix_PlayChannel(-1, soundlist[2], 0);
                    render_boom(&pack2[i], &timeout_anim_boom, &counter_ren_boom);
                    if (temp_ex == ex[4]) {
                        counter_ren_boom = 5;
                        continue;
                    }
                }
                
            }

            for (int i = 0; i < 3; i++) {
                if (pack3[i]->en_bullet.on_display) {
                        renderTexture(bullet, ren_mainplane, pack3[i]->en_bullet.x, pack3[i]->en_bullet.y, 20, 20);
                        enemy_ammo_fly(pack3[i], main_ship.x, main_ship.y);
                }
                if (pack3[i]->on_display) {
                    render_enemy(&pack3[i], &timeout_anim_enemy3, &counter_ren);
                }
                else if(pack3[i]->is_boom) {
                    Mix_PlayChannel(-1, soundlist[2], 0);
                   render_boom(&pack3[i], &timeout_anim_boom, &counter_ren_boom);
                    if (temp_ex == ex[4]) {
                        counter_ren_boom = 5;
                        continue;
                    }
                }
                
            }

           if (pack4->on_display) {
                    render_enemy(&pack4, &timeout_anim_enemy4, &counter_ren);
                    if (pack4->is_shoot && !pack4->burst) {
                        for (int i = pack4->y_enemy; i < 1000; i++) {
                                    renderTexture(bullet, ren_mainplane, pack4->x_enemy + 190, pack4->y_enemy + 330 + i, 20, 20);
                                    renderTexture(bullet, ren_mainplane, pack4->x_enemy + 190 - 90, pack4->y_enemy + 330 - 75 + i, 20, 20);
                                    renderTexture(bullet, ren_mainplane, pack4->x_enemy + 190 + 90, pack4->y_enemy + 330 - 75 + i, 20, 20);
                        }
                    }
                    else if (pack4->burst) {
                        //1
                        for (int i = pack4->y_enemy; i < 1000; i++){
                            for (int j = 0; j < 40; j++) {
                                if((pack4->x_enemy + 180 + j>= x + 48 &&  pack4->x_enemy + 180 + j <= x + 80)
                                || (pack4->x_enemy + 180 + j >= x &&  pack4->x_enemy + 180 + j <= x + 128)) {
                                    if (main_ship.hited) {
                                        break;
                                    }
                                    main_ship.hp-= 2;
                                    main_ship.hited = true;
                                    SDL_AddTimer(2000, invince_fraim, NULL);
                                    break;
                                }
                            }
                            //2
                            for (int j = 0; j < 100; j++) {
                                if((pack4->x_enemy + 180 - 90 + j >= x + 48 &&  pack4->x_enemy + 180 - 90 + j <= x + 80)
                                || (pack4->x_enemy + 180 - 90 + j >= x &&  pack4->x_enemy + 180 - 90 + j <= x + 128)) {
                                    if (main_ship.hited) {
                                        break;
                                    }
                                    main_ship.hp-= 2;
                                    main_ship.hited = true;
                                    SDL_AddTimer(2000, invince_fraim, NULL);
                                    break;
                                }
                            }
                            //3
                            for (int j = 0; j < 40; j++) {
                                if((pack4->x_enemy + 180 + 90 + j>= x + 48 &&  pack4->x_enemy + 180 + 90 + j <= x + 80)
                                || (pack4->x_enemy + 180 + 90 + j >= x &&  pack4->x_enemy + 180 + 90 + j <= x + 128)) {
                                    if (main_ship.hited) {
                                        break;
                                    }
                                    main_ship.hp-= 2;
                                    main_ship.hited = true;
                                    SDL_AddTimer(2000, invince_fraim, NULL);
                                    break;
                                }
                            }
                            Mix_PlayChannel(-1, soundlist[5], 0);
                            renderTexture(bullet1, ren_mainplane, pack4->x_enemy + 180, pack4->y_enemy + 330 + i, 40, 40);
                            renderTexture(bullet1, ren_mainplane, pack4->x_enemy + 180 - 90, pack4->y_enemy + 330 - 75 + i, 40, 40);
                            renderTexture(bullet1, ren_mainplane, pack4->x_enemy + 180 + 90, pack4->y_enemy + 330 - 75 + i, 40, 40);
                        }
                    }
                        
                }
                else if(pack4->is_boom) {
                    Mix_PlayChannel(-1, soundlist[2], 0);
                    render_boom(&pack4, &timeout_anim_boom, &counter_ren_boom);
                    if (temp_ex == ex[4]) {
                        counter_ren_boom = 5;
                        continue;
                    }  
                }
            
            

            if (back[0] > SCREEN_HEIGHT) {
                back[0] = -9200;
            }

            if (back[1] > SCREEN_HEIGHT) {
                back[1] = -9200;
            }

            back[0]+=0.2 * 4;
            back[1]+=0.2 * 4;
            mv_pack(packs, x, y, &pack_on_display);

        if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout_timer)){
            score+=10;
            timeout_timer = SDL_GetTicks() + 1000;
        }
        sprintf(sc_str, "%i", score);
        SDL_Color color = { 255,224,12,255 };
        
        renderTextureWithout(renderText("XP", "resource/text/ttf/PressStart2P-Regular.ttf", color, 36, ren_mainplane),ren_mainplane, 25, 12);
        SDL_Color color1 = { 255, 255, 255, 255 };
       renderTextureWithout(renderText(sc_str, "resource/text/ttf/PressStart2P-Regular.ttf", color1, 25, ren_mainplane),ren_mainplane, 120, 17);
        
        switch(main_ship.hp) {
            case 0:
                run = false;
                hp_current = health_bar[0];
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }// сердца закончились гейм овер
                break;
            case 1:
                hp_current = health_bar[1];
                break;
            case 2:
                hp_current = health_bar[2];
                break;
            case 3:
                hp_current = health_bar[3];
                break;
            case 4:
                hp_current = health_bar[4];
                break;
            case 5:
                hp_current = health_bar[5];
                break;
            default:
                run = false;
                IS_GAME_OVER = true;
                while(IS_GAME_OVER)
                {
                    game_over(ren_mainplane);
                }// сердца закончились гейм овер
                hp_current = health_bar[0];
                break; 
        }
        renderTextureWithout(hp_current,ren_mainplane, 570, 10);
        
        if(!reload) {
            sprintf(ammo_str, "%i", 50 - ammo_count);
            SDL_Color color = { 255, 255, 255, 255 };
        
            renderTextureWithout(renderText(ammo_str, "resource/text/ttf/PressStart2P-Regular.ttf", color, 38, ren_mainplane),ren_mainplane, 650,950);
        }
        else {
            
            if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout_reload)) {
                reload_current = reload_tex[sprait_reload_i];
                timeout_reload = SDL_GetTicks() + 25;
                sprait_reload_i++;
                if (sprait_reload_i == 8) {
                    sprait_reload_i = 0;
                }
            }
        
            renderTexture(reload_current, ren_mainplane, 650, 930, 80, 70);
        }

        renderTexture(ammo_icon, ren_mainplane, 725, 925, 75, 75);
        
        SDL_RenderPresent(ren_mainplane);
    }

    if (atoi(h_score) < score) {
        char n_score[256];
        sprintf(n_score, "%i", score);
        file = open("resource/text/high_score.txt", O_WRONLY, O_TRUNC);
        write(file, n_score, strlen(n_score));
        close(file);   
    }

    // endscreen    main menu

    quit_music(playlist_size, soundlist_size, playlist, soundlist);
    return quit();
}
