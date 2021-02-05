#include "timer.h"
#include "SDL2/SDL.h"

void Timer::initTimer(){
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::startTimer(){
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::stopTimer(){
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::pauseTimer(){
	if(started && !paused){
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::unpauseTimer(){
	if(started && paused){
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::getTicks(){
	Uint32 time = 0;
	if(started){
		if(paused){
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}
	return time;
}


bool Timer::isPaused(){
	return paused && started;
}