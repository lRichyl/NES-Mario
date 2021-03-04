#pragma once
#include "sprite.h"
#include "entity.h"
#include "tile.h"
#include "SDL2/SDL.h"
#include "vector2df.h"

struct Goomba : public Entity{
     Goomba();

     float speed = 1000;
     int direction = -1;

     Sprite *currentAnimation;
     Sprite walkingAnimation;
     Sprite dyingAnimation;

     void update(float deltaTime, SDL_Rect *camera) override;
     void draw()override;
     void updatePosition();
	void initializeAnimationFrames();
	void onCollision(Vector2df penetration) override;
     Entity *clone()override{
		Entity::IDcount++;
		ID = Entity::IDcount;
		return new Goomba(*this);}
};
