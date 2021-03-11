#include "music.h"
#include <iostream>
// #include "SDL2/SDL_mixer.h"

void Music::loadMusicFile(const char *fileName){
     music = Mix_LoadMUS(fileName);
     if(music == nullptr){
        std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void Music::play(){
     if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic(music, -1 );
        }
}

// void Music::stop(){
//      Mix_HaltMusic();
// }
