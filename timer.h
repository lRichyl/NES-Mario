#ifndef TIMER_H
#define TIMER_H
#include <cstdint>
#include "SDL2/SDL.h"
struct Timer{
	bool paused;
	bool started;
	Uint32 startTicks;
	Uint32 pausedTicks;
	
	void initTimer();
	void startTimer();
	void stopTimer();
	void pauseTimer();
	void unpauseTimer();
	Uint32 getTicks();
	bool isPaused();	
};

#endif