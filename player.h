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
	Vector2df velocity = Vector2df(0, 0);
	Vector2df acceleration = Vector2df(60, 0);
	float gravity = 10;
	float distanceTraveled = 0;
	int maxVelocity = 2;
	int xdirection = 1;
	int ydirection = 1;
	bool canJump = true;
	bool isFalling = false;
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
