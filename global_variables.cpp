#include "global_variables.h"


SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
SDL_Surface *screenSurface = nullptr;
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
SDL_Rect CAMERA;
// int RENDERER_WIDTH = getRendererWidth();
// int RENDERER_HEIGHT = getRendererHeight();
RendererInformation rendererInfo;
float deltaT = 0;

SDL_Window *editorWindow = nullptr;
