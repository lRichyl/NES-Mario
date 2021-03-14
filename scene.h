#pragma once
#include "tile_map.h"
#include "entity.h"
#include "global_variables.h"
#include <vector>
#include "texture.h"
#include "collision.h"

struct Scene{
	Scene();
	int levelWidth;
	int levelHeight;
	SDL_Texture *tileset;
	// SDL_Rect camera;

	CollisionManager collisionManager;

	TileMap layer0;		//This layer is used to draw the background
	TileMap layer1;		//Next layer after the background. The player and other dynamic entities will "walk" over this layer
	TileMap layer2;		//Collisions will be checked between this entities.
	TileMap layer3;		//Holds all the entities that will be closer to the screen and drawn over the player.

	// void setScale(float xScale, float yScale);
	void unloadEntities();
	void resetCamera();
	void updateScene(float deltaTime);
	void checkCollisions();
	void setPositionInCamera();
	void drawScene();

};
