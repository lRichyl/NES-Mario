#pragma once
#include "SDL2/SDL_mixer.h"

struct Music{
     Mix_Music *music = nullptr;

     void loadMusicFile(const char *fileName);
     void play();
     // void stop();
     ~Music(){
          // Mix_FreeMusic(music);
     }
};

struct MusicContainer{
     Mix_Music *overWorldTheme;
     Mix_Music *undergroundTheme;

     void initMusicContainer();
     ~MusicContainer(){
          Mix_FreeMusic(overWorldTheme);
          Mix_FreeMusic(undergroundTheme);
     }
};
