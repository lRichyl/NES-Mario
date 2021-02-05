#ifndef SCENE_H
#define SCENE_H
#include "tile_map.h"
#include "entity.h"
#include "global_variables.h"
#include <vector>
#include "texture.h"

struct Scene{
	int levelWidth;
	int levelHeight;
	SDL_Texture *tileset;
	SDL_Rect *camera;
	
	TileMap layer0;		//This layer is used to draw the background
	TileMap layer1;		//Next layer after the background. The player and other dynamic entities will "walk" above this layer 
	TileMap layer2;		//Collisions will be checked between this entities.
	TileMap layer3;		//Holds all the entities that will be closer to the screen and drawn above the player.
	
	// void setScale(float xScale, float yScale);
	void updateScene(float deltaTime);
	void setPositionInCamera();
	void drawScene();
	
};

#endif