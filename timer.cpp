#include "timer.h"
#include "SDL2/SDL.h"

Timer::Timer(){
     startingTime = 0;
     finalTime = 0;
     timeDifference = 0;
     timeSum = 0;
}

void Timer::countTo(float timeInMilliseconds){
     if(timeReached == true) timeReached = false;
     if(timeSum >= timeInMilliseconds){
          timeReached = true;
          timeSum = 0;
     }
     startingTime = (float)SDL_GetTicks() /1000.f;
     timeDifference = startingTime - finalTime;
     timeSum += timeDifference;
     finalTime = startingTime;



}
