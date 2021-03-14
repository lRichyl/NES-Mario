#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include "SDL2/SDL.h"
#include "renderer.h"
#include "camera.h"
#include "texture.h"
#include "sound_effects.h"
#include "music.h"


extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern SDL_Surface *screenSurface;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern Camera CAMERA;
// extern int RENDERER_WIDTH;
// extern int RENDERER_HEIGHT;
extern RendererInformation rendererInfo;
extern float deltaT;
extern double deltaTfixed;

extern TextureContainer texturesContainer;
extern SoundsContainer soundsContainer;
extern MusicContainer musicContainer;

#endif
