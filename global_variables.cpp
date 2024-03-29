#include "global_variables.h"


SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
SDL_Surface *screenSurface = nullptr;
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
Camera CAMERA;
SDL_Event globalEvent;
// int RENDERER_WIDTH = getRendererWidth();
// int RENDERER_HEIGHT = getRendererHeight();
RendererInformation rendererInfo;
float deltaT = 0;
double deltaTfixed = 1.f/60.f;

TextureContainer texturesContainer;
SoundsContainer soundsContainer;
MusicContainer musicContainer;
GlyphsMap marioFont;
