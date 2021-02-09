#ifndef ENTITY_H
#define ENTITY_H
#include "sprite.h"

enum ENTITY_TYPE {
	DYNAMIC,
	PLAYER,
	GROUND,
	BRICK,
	QUESTIONMARK,
	CLOUDLEFTTOP,
	CLOUDLEFTDOWN,
	CLOUDRIGHTTOP,
	CLOUDRIGHTDOWN,
	PIPELEFTTOP,
	PIPELEFTDOWN,
	PIPERIGHTTOP,
	PIPERIGHTDOWN
 };

struct Entity{
	static int IDcount;
	int ID;
	bool isActive;
	float x = 0;
	float y = 0;
	int xTile;
	int yTile;
	bool isStatic = true;
	Sprite sprite;
	SDL_Rect clippingBox;
	ENTITY_TYPE entityType;
	// int xTileNumber;
	// int yTileNumber;

	Entity();
	virtual void update(float deltaTime, SDL_Rect *camera) = 0;
	virtual void draw() = 0;
	void setTileSize(int tileSize);
	virtual Entity *clone() = 0;
	virtual ~Entity() = default;

	void setClippingBox(int x, int y, int w, int h);
};
#endif
