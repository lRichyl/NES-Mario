#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"
#include "timer.h"
#include <string>
#include <vector>

struct Sprite{
	~Sprite();
	// SDL_Rect boundingBox {}; // Remove this
	SDL_Rect *bBox = nullptr;
	bool flip = false;
	std::vector<SDL_Rect> frames;
	float timeCount = 0;
	unsigned int frameIndex = 0;
	float timeSum = 0;
	float startingTime;
	float finalTime;
	Timer timer;
	SDL_Texture *texture = NULL;

	void update(float wishedTimePerFrame);
	void animateSprite();
	void setTexture(std::string);

};
#endif
