#pragma once
#include "sprite.h"
#include "vector2df.h"
#include "vector2di.h"
#include "camera.h"

enum ENTITY_TYPE{
	ENTITY_PLAYER,
	ENTITY_MIN = ENTITY_PLAYER,
	ENTITY_GOOMBA,
	ENTITY_ITEM,
	ENTITY_GROUND,
	ENTITY_SOLIDBLOCK,
	ENTITY_BRICK,
	ENTITY_QUESTIONMARK,
	ENTITY_CLOUD,
	ENTITY_PIPELEFTTOP,
	ENTITY_PIPELEFTDOWN,
	ENTITY_PIPERIGHTTOP,
	ENTITY_PIPERIGHTDOWN,
	ENTITY_MOUNTAIN,
	ENTITY_MAX = ENTITY_MOUNTAIN
 };

enum ITEM_TYPE{
	ITEM_MUSHROOM,
	ITEM_MIN = ITEM_MUSHROOM,
	ITEM_FIRE_FLOWER,
	ITEM_STAR,
	ITEM_EXTRA_LIFE,
	ITEM_MAX = ITEM_EXTRA_LIFE
};

struct Entity{
	static int IDcount;
	int ID;
	bool isActive  = true; //When this is false the entity stops being updated and drawn
	bool isDestroyed = false;
	Vector2df position;
	Vector2df velocity;
	int xTile;
	int yTile;
	bool isStatic = true;  //This is used to indicate that the entity is part of the scenery
	// Sprite sprite;
	SDL_Rect boundingBox;
	ENTITY_TYPE entityType;
	Sprite *currentAnimation;

	Camera localCamera;

	Entity();
	virtual void update(float deltaTime, Camera *camera) = 0;
	virtual void draw() = 0;
	virtual void onStaticEntityCollision(Vector2df,Entity*){};
	virtual void onDynamicEntityCollision(Vector2df,Entity*){};
	virtual void changeVariant(SDL_Event *e){};

	void setTileSize(int tileSize);
	void updatePosition();
	void updateLocalCamera(Camera camera);
	void setInactiveIfOutsideOfCameraBounds();
	void disableAndDestroyEntity();
	void updateCurrentSprite();
	virtual Entity *clone() = 0;
	virtual ~Entity() {};

};
