#pragma once
#include <iostream>
#include <vector>
#include "global_variables.h"
#include "entity.h"
#include "tile.h"
// struct Tile;
using namespace std;


struct TileMap{
	int levelWidth = 10000; // This size is in pixels
	int levelHeight = 10000;
	int tileWidth = Tile::tileSize;
	int tileHeight = Tile::tileSize;

	vector<vector<Entity*>> entities {};
	vector<Entity*> dynamicEntities {};

	TileMap();
	~TileMap();

	bool addEntityOnTile(int xTile, int yTile, Entity *e);
	void emptyTilemap();


	int getXTile(float xPosition);
	int getYTile(float yPositiion);
	void update(float deltaT, Camera *camera);
	void draw();
};
