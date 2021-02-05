#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "sprite.h"

struct Player : public Entity{	
	Player(){	
		entityType = ENTITY_TYPE::PLAYER;
		isStatic = false;
	}
	float velocity = 100.f;
	
	
	void update(float deltaTime, SDL_Rect *camera) override;
	void draw()override;
	Entity *clone()override{return new Player(*this);}
};
#endif