#pragma once
#include "entity.h"
#include "sprite.h"
#include "texture.h"
#include "vector2df.h"
#include "sound_effects.h"
#include "camera.h"

struct Player : public Entity{

	enum PlayerState{
		NORMAL,
		GROWING,
		SHRINKING,
		PICKING_FIRE,
		DEAD
	};

	Player();
	~Player();
	Vector2df acceleration = Vector2df(25, 0);
	float friction = 15;
	float gravity = 40;
	float distanceTraveled = 0;
	float maxXVelocity = 8;
	float maxYVelocity = 10;
	int   velocityToPlayTurningSound = 3;
	float maxTimePerAnimFrame= 20;
	float timePerAnimFrameFactor;
	float timePerAnimFrame;

	bool isAirborne = true;
	bool canJump = true;
	bool wasBReleased = false;
	bool canSetJumpingSpeed = true;

	PlayerState state = PlayerState::NORMAL;

	Sprite *currentAnimation = nullptr;
	Sprite idleAnimation;
	Sprite walkingAnimation;
	Sprite jumpingAnimation;
	Sprite turningAnimation;

	SoundEffect jumpSound;
	SoundEffect skidSound;

	// Camera localCamera;


	void update(float deltaTime, Camera *camera) override;
	// void updatePosition();
	void draw()override;
	void initializeAnimationFrames();
	void initializeSoundEffects();
	void onStaticEntityCollision(Vector2df penetration,Entity *entity) override;
	void onDynamicEntityCollision(Vector2df penetration,Entity *entity) override;
	void collidingWithTheFloor(Vector2df penetration);
	void collidingWithQuestionMarkBlock(Vector2df penetration, Entity *e);
	Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new Player(*this);}
};
