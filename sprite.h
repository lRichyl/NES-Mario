#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include <string>
#include <vector>

struct Sprite{
	Sprite() = default;
	~Sprite();
	SDL_Rect boundingBox {}; // Remove this
	SDL_Rect *bBox;
	std::vector<SDL_Rect> frames;
	float timeCount = 0;
	int frameIndex = 0;
	float timeSum = 0;
	float startingTime;
	float finalTime;
	SDL_Texture *texture = NULL;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	void animateSprite(float wishedTimePerFrame);
	void setTexture(std::string);

};
#endif
