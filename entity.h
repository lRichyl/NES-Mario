#ifndef ENTITY_H
#define ENTITY_H
#include "sprite.h"
#include "vector2df.h"
#include "vector2di.h"

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
	Vector2df position;
	int xTile;
	int yTile;
	bool isStatic = true;
	Sprite sprite;
	SDL_Rect clippingBox;
	SDL_Rect boundingBox;
	ENTITY_TYPE entityType;
	// int xTileNumber;
	// int yTileNumber;

	Entity();
	virtual void update(float deltaTime, SDL_Rect *camera) = 0;
	virtual void draw() = 0;
	virtual void onCollision(Vector2df){};
	void setTileSize(int tileSize);
	virtual Entity *clone() = 0;
	virtual ~Entity() = default;

	void setClippingBox(int x, int y, int w, int h);
};
#endif
