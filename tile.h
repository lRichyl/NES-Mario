#pragma once
#include "entity.h"
#include "sprite.h"
#include "global_variables.h"
#include "texture.h"



struct Tile : public Entity{
	Tile();
	Tile::Tile(SDL_Texture *texture, SDL_Rect clippingBox, ENTITY_TYPE type, bool isStatic = true);
	static int tileSize;
	Sprite sprite;
	SDL_Rect clippingBox;

	void setClippingBox(int x, int y, int w, int h);
	void update(float deltaTime, Camera *camera)override;
	void draw()override;


	//This should be in the QuestionMarkTile type but it cannot be downcasted
	//from entity



	Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new Tile(*this);}
};

struct PlayerTile : public Tile{
	PlayerTile(){
	sprite.texture = texturesContainer.marioAnimations;
	isStatic = false;
	setClippingBox(98, 32, 12, 16);
	entityType = ENTITY_PLAYER;
	}

};
struct GoombaTile : public Tile{
	GoombaTile(){
	sprite.texture = texturesContainer.enemiesAnimations;
	isStatic = false;
	setClippingBox(1, 28, 16, 16);
	entityType = ENTITY_GOOMBA;
	}

};

struct QuestionMarkTile : public Tile {
	ITEM_TYPE itemType = ITEM_MUSHROOM;

	int selectedItemType = 0;
	int itemTypeCount = 0;
	// QuestionMarkTile();

	QuestionMarkTile(){
		sprite.texture = texturesContainer.marioBlocks;
		isStatic = true;
		setClippingBox(384, 0, 16, 16);
		entityType = ENTITY_QUESTIONMARK;
	}
	void setItemType(int selectedItemType);
	void changeVariant(SDL_Event *e)override;

	Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new QuestionMarkTile(*this);}
};

struct Ground : public Tile{
	Ground(){
	setClippingBox(0, 0, 16, 16 );
	entityType = ENTITY_GROUND;
	}
};
struct SolidBlock : public Tile{
	SolidBlock(){
	setClippingBox(0, 16, 16, 16 );
	entityType = ENTITY_SOLIDBLOCK;
	}
};

struct Brick : public Tile{
	Brick(){
	setClippingBox(16, 0, 16, 16 );
	entityType = ENTITY_BRICK;
	}
};



struct CloudLeftTop : public Tile{
	CloudLeftTop(){
	setClippingBox(8, 320, 16, 16 );
	entityType = ENTITY_CLOUD;
	}
};

struct CloudLeftDown : public Tile{
	CloudLeftDown(){
	setClippingBox(8, 336, 16, 16 );
	entityType = ENTITY_CLOUD;
	}
};
struct CloudRightTop : public Tile{
	CloudRightTop(){
	setClippingBox(24, 320, 16, 16 );
	entityType = ENTITY_CLOUD;
	}
};
struct CloudRightDown : public Tile{
	CloudRightDown(){
	setClippingBox(24, 336, 16, 16 );
	entityType = ENTITY_CLOUD;
	}
};
struct PipeLeftTop : public Tile{
	PipeLeftTop(){
	setClippingBox(0, 128, 16, 16 );
	entityType = ENTITY_PIPELEFTTOP;
	}
};
struct PipeLeftDown : public Tile{
	PipeLeftDown(){
	setClippingBox(0, 144, 16, 16 );
	entityType = ENTITY_PIPELEFTDOWN;
	}
};
struct PipeRightTop : public Tile{
	PipeRightTop(){
	setClippingBox(16, 128, 16, 16 );
	entityType = ENTITY_PIPERIGHTTOP;
	}
};
struct PipeRightDown : public Tile{
	PipeRightDown(){
	setClippingBox(16, 144, 16, 16 );
	entityType = ENTITY_PIPERIGHTDOWN;
	}
};
struct MountTopLeft : public Tile{
	MountTopLeft(){
	setClippingBox(128, 128, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
struct MountTopRight : public Tile{
	MountTopRight(){
	setClippingBox(160, 128, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
struct MountDownLeft : public Tile{
	MountDownLeft(){
	setClippingBox(128, 144, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
struct MountDownRight : public Tile{
	MountDownRight(){
	setClippingBox(160, 144, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
struct MountTop : public Tile{
	MountTop(){
	setClippingBox(144, 128, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
struct MountDown : public Tile{
	MountDown(){
	setClippingBox(144, 144, 16, 16 );
	entityType = ENTITY_MOUNTAIN;
	}
};
