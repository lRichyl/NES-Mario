#pragma once
#include "SDL2/SDL_mixer.h"

struct SoundEffect{
     Mix_Chunk *sound = nullptr;
     int channel;

     void loadSoundFile(const char *fileName);
     void play();
     void stop();
     ~SoundEffect(){
          Mix_FreeChunk(sound);
     }
};
