#include "sound_effects.h"
#include <iostream>
#include "global_variables.h"

void SoundEffect::loadSoundFile(const char *fileName){
     sound = Mix_LoadWAV(fileName);
     if(sound == nullptr){
        std::cout << "Failed to load sound SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Missing file",
                            "Sound file not found. Make sure there's an assets folder.",
                            window);
          exit(1);
    }
}

//This function stops whatever is playing currently in the selected channel
void SoundEffect::play(){
     // if(interrupt && Mix_Playing(channel)) stop();
     if(!interrupt){
          interrupt = true;
          Mix_HaltChannel(channel);
          if(Mix_Playing(channel) == 0){
               Mix_PlayChannel(channel, sound, 0);
          }
     }
}

void SoundEffect::stop(){
     Mix_HaltChannel(channel);
     interrupt = false;
}

void SoundsContainer::initSoundsContainer(){
     marioJump = Mix_LoadWAV("assets/sounds/Jump.wav");
     squish = Mix_LoadWAV("assets/sounds/Squish1.wav");
}
