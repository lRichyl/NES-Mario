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
	Vector2df acceleration = Vector2df(1000, -100);
	float friction = 4;
	float gravity = 8;
	float distanceTraveled = 0;
	int maxXVelocity = 1;
	int maxYVelocity = 2;
	// int xdirection = 1;
	// int ydirection = 1;
	bool isAirborne = false;
	bool canJump = true;
	bool wasBReleased = false;
	bool canSetJumpingSpeed = true;
	// SDL_Rect boundingBox;
	Sprite *currentAnimation = nullptr;
	Sprite idleAnimation;
	Sprite walkingAnimation;
	Sprite jumpingAnimation;


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
