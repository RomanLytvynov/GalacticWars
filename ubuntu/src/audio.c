#include "../inc/header.h"

bool load_sounds(const int size, Mix_Chunk **soundlist) {
    soundlist[0] = Mix_LoadWAV("resource/audio/sounds/click_1.wav");
    soundlist[1] = Mix_LoadWAV("resource/audio/sounds/explosion_1.wav");
    soundlist[2] = Mix_LoadWAV("resource/audio/sounds/explosion_2.wav");
    soundlist[3] = Mix_LoadWAV("resource/audio/sounds/explosion_main_3.wav");
    soundlist[4] = Mix_LoadWAV("resource/audio/sounds/laser_1.wav");
    soundlist[5] = Mix_LoadWAV("resource/audio/sounds/burst.wav");
    soundlist[6] = Mix_LoadWAV("resource/audio/sounds/shot_1.wav");
    soundlist[7] = Mix_LoadWAV("resource/audio/sounds/charge.wav");
    
    for (int i = 0; i < size; i++) {
        if( soundlist[i] == NULL ) {
            printf( "Failed to load sound - %d! SDL_mixer Error: %s\n", i, Mix_GetError() );
            return false;
        }
    }

    return true;
}

bool Load_music(const int size, Mix_Music **playlist) {
    
    playlist[0] = Mix_LoadMUS("resource/audio/ost/0.mp3");
    playlist[1] = Mix_LoadMUS("resource/audio/ost/1.mp3");
    playlist[2] = Mix_LoadMUS("resource/audio/ost/2.mp3");
    playlist[3] = Mix_LoadMUS("resource/audio/ost/3.mp3");
    playlist[4] = Mix_LoadMUS("resource/audio/ost/4.mp3");
    playlist[5] = Mix_LoadMUS("resource/audio/ost/5.mp3");
    playlist[6] = Mix_LoadMUS("resource/audio/ost/6.mp3");
    playlist[7] = Mix_LoadMUS("resource/audio/ost/7.mp3");
    playlist[8] = Mix_LoadMUS("resource/audio/ost/8.mp3");
    playlist[9] = Mix_LoadMUS("resource/audio/ost/9.mp3");

    for (int i = 0; i < size; i++) {
        if( playlist[i] == NULL ) {
            printf( "Failed to load beat music - %d! SDL_mixer Error: %s\n", i, Mix_GetError() );
            return false;
        }
    }
    
    return true;
}

void quit_music(const int playlist_size, const int soundlist_size, Mix_Music **playlist, Mix_Chunk **soundlist) {
    /////
    for (int i = 0; i < playlist_size; i++) {
        Mix_FreeMusic( playlist[i] );
        playlist[i] = NULL;
    }
    /////
    for (int i = 0; i < soundlist_size; i++) {
        Mix_FreeChunk( soundlist[i] );
        soundlist[i] = NULL;
    }
}
