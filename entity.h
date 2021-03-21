#pragma once
#include "sprite.h"
#include "vector2df.h"
#include "vector2di.h"
#include "camera.h"

enum class ENTITY_TYPE{
	PLAYER,
	MIN = PLAYER,
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
	MOUNTAIN,
	MAX = MOUNTAIN
 };

enum class ITEM_TYPE{
	MUSHROOM,
	MIN = MUSHROOM,
	FIRE_FLOWER,
	STAR,
	EXTRA_LIFE,
	MAX = EXTRA_LIFE
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
	// Sprite sprite;
	SDL_Rect clippingBox;
	SDL_Rect boundingBox;
	ENTITY_TYPE entityType;

	Camera localCamera;

	Entity();
	virtual void update(float deltaTime, Camera *camera) = 0;
	virtual void draw() = 0;
	virtual void onStaticEntityCollision(Vector2df,Entity*){};
	virtual void onDynamicEntityCollision(Vector2df,Entity*){};
	virtual void changeVariant(SDL_Event *e){};
	void setTileSize(int tileSize);
	void updatePosition();
	virtual Entity *clone() = 0;
	virtual ~Entity() {};

	void setClippingBox(int x, int y, int w, int h);
};
