#ifndef ENTITY_H
#define ENTITY_H
#include "sprite.h"
#include "vector2df.h"
#include "vector2di.h"

enum ENTITY_TYPE {
	PLAYER,
	GOOMBA,
	GROUND,
	SOLIDBLOCK,
	BRICK,
	QUESTIONMARK,
	CLOUD,
	PIPELEFTTOP,
	PIPELEFTDOWN,
	PIPERIGHTTOP,
	PIPERIGHTDOWN,
	MOUNTAIN
 };

enum ITEM_TYPE{
	MUSHROOM,
	FIRE_FLOWER,
	STAR,
	EXTRA_LIFE
};

struct Entity{
	static int IDcount;
	int ID;
	bool isActive  = true; //When this is false the entity stops being updated and drawn
	Vector2df position;
	Vector2df velocity;
	int xTile;
	int yTile;
	bool isStatic = true;  //This is used to indicate that the entity is part of the scenery
	Sprite sprite;
	SDL_Rect clippingBox;
	SDL_Rect boundingBox;
	ENTITY_TYPE entityType;
	// int xTileNumber;
	// int yTileNumber;

	Entity();
	virtual void update(float deltaTime, SDL_Rect *camera) = 0;
	virtual void draw() = 0;
	virtual void onStaticEntityCollision(Vector2df,Entity*){};
	virtual void onDynamicEntityCollision(Vector2df,Entity*){};
	void setTileSize(int tileSize);
	virtual Entity *clone() = 0;
	virtual ~Entity() = default;

	void setClippingBox(int x, int y, int w, int h);
};
#endif
