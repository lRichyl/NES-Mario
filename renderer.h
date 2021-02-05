#pragma once
#include "SDL2/SDL.h"



struct RendererInformation{
	RendererInformation();
	int width;
	int height;
	
	void getRendererSize();
};