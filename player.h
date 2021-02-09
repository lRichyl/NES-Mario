#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "sprite.h"
#include "texture.h"

struct Player : public Entity{
	Player(){
		entityType = ENTITY_TYPE::PLAYER;
		isStatic = false;
		isActive = true;
		sprite.texture = loadTexture("assets/textures/mario_animations.png");
		sprite.boundingBox.w = 64;
		sprite.boundingBox.h = 64;
		setClippingBox(98, 32, 12, 16);
	}
	float velocity = 100.f;


	void update(float deltaTime, SDL_Rect *camera) override;
	void draw()override;
	Entity *clone()override{
		Entity::IDcount++;
		ID = Entity::IDcount;
		return new Player(*this);}
};
#endif
