#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "sprite.h"
#include "texture.h"
#include "vector2df.h"
#include "sound_effects.h"
// #include "vector2di.h"

struct Player : public Entity{
	Player();
	~Player();
	Vector2df acceleration = Vector2df(80, 0);
	float friction = 25;
	float gravity = 40;
	float distanceTraveled = 0;
	float maxXVelocity = 6;
	float maxYVelocity = 10;
	// int xdirection = 1;
	// int ydirection = 1;
	bool isAirborne = true;
	bool canJump = true;
	bool wasBReleased = false;
	bool canSetJumpingSpeed = true;
	// SDL_Rect boundingBox;
	Sprite *currentAnimation = nullptr;
	Sprite idleAnimation;
	Sprite walkingAnimation;
	Sprite jumpingAnimation;

	SoundEffect jumpSound;


	void update(float deltaTime, SDL_Rect *camera) override;
	void updatePosition();
	void draw()override;
	void initializeAnimationFrames();
	void initializeSoundEffects();
	void onStaticEntityCollision(Vector2df penetration,Entity *entity) override;
	void onDynamicEntityCollision(Vector2df penetration,Entity *entity) override;
	void collidingWithTheFloor(Vector2df penetration);
	Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new Player(*this);}
};
#endif
