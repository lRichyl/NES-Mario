#include "sound_effects.h"
#include <iostream>

void SoundEffect::loadSoundFile(const char *fileName){
     sound = Mix_LoadWAV(fileName);
     if(sound == nullptr){
        std::cout << "Failed to load sound SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void SoundEffect::play(){
     // if(interrupt && Mix_Playing(channel)) stop();
     if(Mix_Playing(channel) == 0){
          Mix_PlayChannel(channel, sound, 0);
     }
}
 void SoundEffect::stop(){
     Mix_HaltChannel(channel);
}
