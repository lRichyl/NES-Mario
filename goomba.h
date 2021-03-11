#pragma once
#include "sprite.h"
#include "entity.h"
#include "tile.h"
#include "SDL2/SDL.h"
#include "vector2df.h"

struct Goomba : public Entity{
     Goomba();

     float speed = 45;
     float gravity = 40;
     int direction = -1;

     Sprite *currentAnimation;
     Sprite walkingAnimation;
     Sprite dyingAnimation;

     void update(float deltaTime, SDL_Rect *camera) override;
     void draw()override;
     void updatePosition();
	void initializeAnimationFrames();
	void onStaticEntityCollision(Vector2df penetration, Entity *e) override;
     // void onDynamicEntityCollision(Vector2df penetration, Entity *e) override;
     Entity *clone()override{
          ID = Entity::IDcount;
		Entity::IDcount++;
		return new Goomba(*this);}
};
