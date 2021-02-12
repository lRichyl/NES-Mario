#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "sprite.h"
#include "texture.h"
#include "vector2df.h"
// #include "vector2di.h"

struct Player : public Entity{
	Player();
	~Player();
	Vector2df velocity = Vector2df(150.0f, 100.0f);
	int xdirection = 1;
	int ydirection = 1;
	// SDL_Rect boundingBox;
	Sprite *currentAnimation = nullptr;
	Sprite idleAnimation;
	Sprite walkingAnimation;


	void update(float deltaTime, SDL_Rect *camera) override;
	void updatePosition();
	void draw()override;
	void initializeAnimationFrames();
	void onCollision(Vector2df penetration) override;
	Entity *clone()override{
		Entity::IDcount++;
		ID = Entity::IDcount;
		return new Player(*this);}
};
#endif
