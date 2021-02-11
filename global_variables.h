#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include "SDL2/SDL.h"
#include "renderer.h"


extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern SDL_Rect CAMERA;
// extern int RENDERER_WIDTH;
// extern int RENDERER_HEIGHT;
extern RendererInformation rendererInfo;
extern float deltaT;

extern SDL_Window *editorWindow;


#endif
