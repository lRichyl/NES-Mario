#include "sprite.h"
#include "texture.h"
#include "global_variables.h"
#include <iostream>

void Sprite::setTexture(std::string path){
	texture = loadTexture(path);
}

void Sprite::animateSprite(float wishedTimePerFrame){
	startingTime = (float)SDL_GetTicks() / 1000.f;
	timeSum += startingTime -= finalTime;
	// std::cout << timeSum << std::endl;
	if(timeSum >= wishedTimePerFrame){
		timeSum = 0;
		frameIndex++;
	}
	if(frameIndex > frames.size() - 1){
		frameIndex = 0;
	}


	SDL_RenderCopy(renderer, texture, &frames[frameIndex],bBox);

	finalTime = (float)SDL_GetTicks() / 1000.f;


}

Sprite::~Sprite(){
	// SDL_DestroyTexture(texture);
}
