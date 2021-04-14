#include "sprite.h"
#include "texture.h"
#include "global_variables.h"
#include "tile_map.h"
#include <iostream>

void Sprite::setTexture(std::string path){
	texture = loadTexture(path);
}

void Sprite::update(float wishedTimePerFrame){
	if(wishedTimePerFrame > 0){
		timer.countTo(wishedTimePerFrame);

		if(timer.timeReached){
			timeSum = 0;
			frameIndex++;
		}
		if(frameIndex > frames.size() - 1){
			frameIndex = 0;
		}

	}
}

void Sprite::animateSprite(){


	if(flip){
		SDL_RenderCopyEx(renderer, texture, &frames[frameIndex],bBox, 0, NULL, SDL_FLIP_HORIZONTAL);
	}else{
		SDL_RenderCopyEx(renderer, texture, &frames[frameIndex],bBox, 0, NULL, SDL_FLIP_NONE);

		// SDL_RenderCopy(renderer, texture, &frames[frameIndex],bBox);
	}
	// std::cout << bBox->x << ", " << bBox->y << std::endl;

	// finalTime = (float)SDL_GetTicks() / 1000.f;


}

Sprite::~Sprite(){
	// SDL_DestroyTexture(texture);
}
