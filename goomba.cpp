#include <iostream>
#include "goomba.h"
#include "SDL2/SDL.h"
#include "global_variables.h"
#include "texture.h"

Goomba::Goomba(){
     entityType = ENTITY_TYPE::GOOMBA;
	isStatic = false;
	isActive = true;
	boundingBox.w = Tile::tileSize;
	boundingBox.h = Tile::tileSize;
     initializeAnimationFrames();
     currentAnimation = &walkingAnimation;
     initializeSoundEffects();
}


void Goomba::update(float deltaTime, Camera *camera){
     // if(isActive){
          localCamera = *camera;
          if(state == GoombaState::NORMAL){
               position.x += direction * speed * deltaTime;
               position.y += gravity * deltaTime;
               updatePosition();
          }
          else if(state == GoombaState::CRUSHED){
               currentAnimation = &dyingAnimation;
               crushingSound.play();
               timeCounter += deltaTime;
               if(timeCounter >= 1) {
                    isActive = false;
               }
          }
}
// void Goomba::updatePosition(){
// 	boundingBox.x = position.x - localCamera.bounds.x;
// 	boundingBox.y = position.y - localCamera.bounds.y;
//
// }
void Goomba::draw(){
          currentAnimation->animateSprite(0.15);
}
void Goomba::initializeAnimationFrames(){
     //---------WALKING ANIMATION----------
     walkingAnimation.texture = texturesContainer.enemiesAnimations;
     walkingAnimation.bBox = &boundingBox;
     walkingAnimation.frames.push_back(SDL_Rect {1, 28, 16, 16});
     walkingAnimation.frames.push_back(SDL_Rect {18, 28, 16, 16});

     //---------DYING ANIMATION----------
     dyingAnimation.texture = texturesContainer.enemiesAnimations;
     dyingAnimation.bBox = &boundingBox;
     dyingAnimation.frames.push_back(SDL_Rect {39, 28, 16, 16});

}
void Goomba::onStaticEntityCollision(Vector2df penetration, Entity *e){
     //When colliding with entities marked as static
     if (penetration.x > 0) {
          direction = -1;
     }
     if(penetration.x < 0){
          direction = 1;
     }


     position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}

void Goomba::initializeSoundEffects(){
     crushingSound.channel = 2;
     crushingSound.sound = soundsContainer.squish;

}

// void Goomba::onDynamicEntityCollision(Vector2df penetration, Entity* e){
//      // if(e->entityType == ENTITY_TYPE::PLAYER){
//      //      // if(penetration.y < 0 && e->velocity.y >= 0) isActive = false;
//      // }
// }
