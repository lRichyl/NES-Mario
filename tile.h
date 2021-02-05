#ifndef TILES_H
#define TILES_H
#include "entity.h"
#include "sprite.h"
#include "global_variables.h"
#include "texture.h"


struct Tile : public Entity{
	Tile();
	
	void setTileSize(int newTileSize);
	void update(float deltaTime, SDL_Rect *camera)override;
	void draw()override;
	
	// THIS IS CREATING A COPY FOR EVERY TILE
	static SDL_Texture *texture;
	static const int tileSize = 64;
	
	Entity *clone()override{return new Tile(*this);}
};

struct Ground : public Tile{
	Ground(){
	setClippingBox(0, 0, 16, 16 ); 
	entityType = ENTITY_TYPE::GROUND;
	}
};
struct Brick : public Tile{
	Brick(){
	setClippingBox(16, 0, 16, 16 ); 
	entityType = ENTITY_TYPE::BRICK;
	}
};
struct QuestionMark : public Tile{
	QuestionMark(){
	setClippingBox(384, 0, 16, 16 ); 
	entityType = ENTITY_TYPE::QUESTIONMARK;
	}
};
struct CloudLeftTop : public Tile{	
	CloudLeftTop(){
	setClippingBox(8, 320, 16, 16 ); 
	entityType = ENTITY_TYPE::CLOUDLEFTTOP;
	}	
};
struct CloudLeftDown : public Tile{	
	CloudLeftDown(){
	setClippingBox(8, 336, 16, 16 ); 
	entityType = ENTITY_TYPE::CLOUDLEFTDOWN;
	}	
};
struct CloudRightTop : public Tile{	
	CloudRightTop(){
	setClippingBox(24, 320, 16, 16 ); 
	entityType = ENTITY_TYPE::CLOUDRIGHTTOP;
	}	
};
struct CloudRightDown : public Tile{	
	CloudRightDown(){
	setClippingBox(24, 336, 16, 16 ); 	
	entityType = ENTITY_TYPE::CLOUDRIGHTDOWN;
	}	
};
struct PipeLeftTop : public Tile{	
	PipeLeftTop(){
	setClippingBox(0, 128, 16, 16 ); 
	entityType = ENTITY_TYPE::PIPELEFTTOP;
	}	
};
struct PipeLeftDown : public Tile{	
	PipeLeftDown(){
	setClippingBox(0, 144, 16, 16 ); 
	entityType = ENTITY_TYPE::PIPELEFTDOWN;
	}	
};
struct PipeRightTop : public Tile{	
	PipeRightTop(){
	setClippingBox(16, 128, 16, 16 ); 
	entityType = ENTITY_TYPE::PIPERIGHTTOP;
	}	
};
struct PipeRightDown : public Tile{	
	PipeRightDown(){
	setClippingBox(16, 144, 16, 16 ); 
	entityType = ENTITY_TYPE::PIPERIGHTDOWN;
	}	
};







#endif