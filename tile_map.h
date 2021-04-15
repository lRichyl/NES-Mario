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

	static bool updateOnlyPlayer;

	vector<vector<Entity*>> entities {};
	// vector<Entity*> dynamicEntities {};

	TileMap();
	// TileMap(const TileMap* tileMap);
	virtual ~TileMap();

	bool addEntityOnTile(int xTile, int yTile, Entity *e);
	int getXTile(float xPosition);
	int getYTile(float yPositiion);


	void copyTileMap(const TileMap *tileMap);
	virtual void update(float deltaT, Camera *camera);
	virtual void draw();
	virtual void emptyTilemap();
};

struct CollisionTileMap : public TileMap{
	vector<Entity*> dynamicEntities {};
	void copyTileMap(const TileMap *tileMap, Camera *camera);
	void update(float deltaT, Camera *camera) override;
	void draw() override;
	void emptyTilemap() override;
	~CollisionTileMap();
};
