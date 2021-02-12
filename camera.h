#pragma once
#include "SDL2/SDL.h"

struct Camera{
     SDL_Rect bounds;
     float xOffset;
     float yOffset;

     Camera();
     void resetCamera();
     void updatePosition();

};
