#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "sprite.h"
#include "texture.h"
#include "vector2df.h"
// #include "vector2di.h"

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
	~Player();
	Vector2df velocity = Vector2df(100.0f, 100.0f);
	int xdirection = 1;
	int ydirection = 1;


	void update(float deltaTime, SDL_Rect *camera) override;
	void updatePosition();
	void draw()override;
	void onCollision(Vector2df penetration) override;
	Entity *clone()override{
		Entity::IDcount++;
		ID = Entity::IDcount;
		return new Player(*this);}
};
#endif
