#pragma once
#include "SDL2/SDL_image.h"
#include <string>


SDL_Texture* loadTexture( std::string path);

struct TextureContainer{
     void initTextureContainer();
     //If we get too many textures this will be put in a map for easier texture addition and access
     SDL_Texture *marioAnimations;
     SDL_Texture *marioBlocks;
     SDL_Texture *enemiesAnimations;
     SDL_Texture *items;

     ~TextureContainer(){
          SDL_DestroyTexture(marioAnimations);
          SDL_DestroyTexture(marioBlocks);
          SDL_DestroyTexture(enemiesAnimations);
          SDL_DestroyTexture(items);
     }
};
