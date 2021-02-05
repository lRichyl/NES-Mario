#ifndef TILE_MAP_H
#define TILE_MAP_H
#include <iostream>
#include <vector>
#include "global_variables.h"
#include "entity.h"
#include "tile.h"
using namespace std;

struct TileMap{
	int levelWidth = 10000; // This size is in pixels
	int levelHeight = 10000;	
	int tileWidth = Tile::tileSize;
	int tileHeight = Tile::tileSize;
	bool initializeDynamicEntities = true;
	// float xScale;
	// float yScale;
	vector<vector<Entity*>> entities {};
	
	TileMap();
	~TileMap();
	bool addEntityByPosition(Entity *e);
	// bool addEntityByTile(Entity *e);
	bool addEntityOnTile(int xTile, int yTile, Entity *e);
	int getXTile(float xPosition);
	int getYTile(float yPosition);
	// void scaleDimensions();
	void update(float deltaT, SDL_Rect *camera);
	void draw();
};
#endif