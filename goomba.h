#pragma once
#include "sprite.h"
#include "entity.h"
#include "tile.h"
#include "SDL2/SDL.h"
#include "vector2df.h"
#include "timer.h"
#include "sound_effects.h"



struct Goomba : public Entity{
     enum GoombaState{
          NORMAL,
          CRUSHED
     };
     Goomba();

     float speed = 45;
     float gravity = 40;
     int direction = -1;
     float timeCounter = 0;;

     GoombaState state = GoombaState::NORMAL;
     // Timer deathTimer;
     Sprite *currentAnimation;
     Sprite walkingAnimation;
     Sprite dyingAnimation;

     SoundEffect crushingSound;

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

     ~Goomba(){}
};
