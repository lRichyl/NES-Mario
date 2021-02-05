#include "global_variables.h"

// int getRendererWidth(){
	// int *width;
	// SDL_GetRendererOutputSize(renderer, width, nullptr);
	// return *width;
// }
// int getRendererHeight(){
	// int *height;
	// SDL_GetRendererOutputSize(renderer, nullptr, height);
	// return *height;
// }

RendererInformation::RendererInformation(){
	getRendererSize();
}

void RendererInformation::getRendererSize(){
	int w;
	int h;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	width = w;
	height = h;
}