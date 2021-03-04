#include "texture.h"
#include "global_variables.h"




SDL_Texture* loadTexture( std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

// SDL_Texture *TextureContainer::marioAnimations = nullptr;
// SDL_Texture *TextureContainer::marioBlocks = nullptr;


void TextureContainer::initTextureContainer(){
     marioAnimations =   loadTexture("assets/textures/mario_animations.png");
     marioBlocks     =   loadTexture("assets/textures/mario_blocks.png");
     enemiesAnimations = loadTexture("assets/textures/enemies.png");
}
