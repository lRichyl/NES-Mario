#pragma once
#include "SDL2/SDL_mixer.h"

struct Music{
     Mix_Music *music = nullptr;

     void loadMusicFile(const char *fileName);
     void play();
     // void stop();
     ~Music(){
          Mix_FreeMusic(music);
     }
};
