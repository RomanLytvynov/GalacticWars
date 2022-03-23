#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "../resource/framework/SDL2_image.framework/Headers/SDL_image.h"
//#include "../resource/framework/SDL2_mixer.framework/Headers/SDL_mixer.h"
//#include "../resource/framework/SDL2_ttf.framework/Headers/SDL_ttf.h"
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct s_bullet {
    int x;
    int y;
    bool on_display;
}               t_bullet;

typedef struct s_ship {
    bool up;
    bool down;
    bool left;
    bool right;
    bool shoot;
    int hp;
    int damage;
    int x;
    int y;
    bool hited;
}              t_ship;

typedef struct s_enemy {
    int x_enemy;
    int y_enemy;
    int hp;
    int pack_num;
    bool on_display;
    bool is_boom;
    bool is_shoot;
    bool burst;
    t_bullet en_bullet;
}               t_enemy;

extern SDL_Renderer *ren_mainplane;
extern SDL_Texture *ex[5];
extern SDL_Texture *temp_ex;
extern SDL_Texture *enemy;
extern int sprite_i;

extern Mix_Chunk *soundlist[8];

extern SDL_Texture *bullet;

extern SDL_Texture *main_ship_tex[12];

extern SDL_Texture *enemy1[3];
extern SDL_Texture *enemy2[3];
extern SDL_Texture *enemy3[3];
extern SDL_Texture *enemy4[3];

extern t_ship main_ship;

extern t_enemy **pack1;
extern t_enemy **pack2;
extern t_enemy **pack3;
extern t_enemy *pack4;

extern t_bullet **ammo;
extern bool IS_MENU;
extern bool RUN;
extern bool IS_SOUND_OFF;
extern bool IS_MUSIC_OFF;
extern bool IS_PAUSE;
extern bool IS_GAME_OVER;
extern bool is_restart;
extern bool kostyl;

extern bool packs_on_display[4];

extern int score;
extern int h_score;
extern int count_packs;
extern Uint32 pack_timeout;

void menu(bool *is_menu, SDL_Renderer *ren);
void pause_game(SDL_Renderer *ren);
void game_over(SDL_Renderer *ren);

SDL_Texture* loadTexture(const char *, SDL_Renderer *);
void renderTextureWithout(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
SDL_Texture* renderText(const char *message, const char *fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);

void render_boom(t_enemy **pack, Uint32 *timeout_anim_boom, int *counter_ren_boom);
void render_enemy(t_enemy **pack, Uint32 *timeout_anim_enemy, unsigned int *counter_ren);
void render_main_ship(Uint32 *timeout_anim, unsigned int *counter_ren);

bool load_sounds(const int, Mix_Chunk **);
bool Load_music(const int, Mix_Music **);
void quit_music(const int, const int, Mix_Music **, Mix_Chunk **);

void doKeyUp(SDL_KeyboardEvent *event);
void doKeyDown(SDL_KeyboardEvent *event);
void doInput(void);

unsigned int init_pack();
void init_pack1(void);
void init_pack2(void);
void spawn_bullet(int x,  int y, t_bullet **ammo, int *a, bool *reload, int *start_reload);

void enemy_spawn_bullet(t_enemy *enemy);
void ship_ammo_fly(t_bullet **ammo, t_enemy ***pack, int i);
void mv_pack(t_enemy ***packs, int x, int y, bool *on_display);
void enemy_ammo_fly(t_enemy *enemy, int x, int y);
void laser_cast(t_enemy *enemy);

int get_size_pack(t_enemy **pack);
SDL_Texture **get_enemy_tex(t_enemy **pack);
unsigned int invince_fraim();

#endif
