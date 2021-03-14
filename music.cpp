#include "music.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "global_variables.h"

void Music::loadMusicFile(const char *fileName){
     music = Mix_LoadMUS(fileName);
     if(music == nullptr){
        std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Missing file",
                            "Music file not found. Make sure there's an assets folder.",
                            window);
          exit(1);
    }
}

void Music::play(){
     if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic(music, -1 );
        }
}

void MusicContainer::initMusicContainer(){
     overWorldTheme = Mix_LoadMUS("assets/music/Running About.mp3");
     undergroundTheme = Mix_LoadMUS("assets/music/Underground.mp3");
}

// void Music::stop(){
//      Mix_HaltMusic();
// }
