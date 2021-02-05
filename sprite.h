#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include <string>

struct Sprite{
	SDL_Rect boundingBox;
	SDL_Texture *texture = NULL;
		
	void setTexture(std::string);
	
};
#endif