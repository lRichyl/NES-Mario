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
     crushingSound.loadSoundFile("assets/sounds/Squish1.wav");
     crushingSound.channel = 2;
}


void Goomba::update(float deltaTime, SDL_Rect *camera){
     if(isActive){
          if(state == GoombaState::NORMAL){
               position.x += direction * speed * deltaTime;
               position.y += gravity * deltaTime;
               // std::cout << "goomba test" << std::endl;
               updatePosition();
               // std::cout << deathTimer.timeSum << std::endl;
          }
          else if(state == GoombaState::CRUSHED){
               currentAnimation = &dyingAnimation;
               // crushingSound.play();
               // deathTimer.countTo(.5);
               timeCounter += deltaTime;
               if(timeCounter >= 1) {
                    isActive = false;
                    // crushingSound.stop();
               }
               // std::cout << this << std::endl;
               // isActive = false;
          }
     }
}
void Goomba::updatePosition(){
	boundingBox.x = position.x - CAMERA.bounds.x;
	boundingBox.y = position.y - CAMERA.bounds.y;
	// std::cout << boundingBox.x << " , " << boundingBox.x << std::endl;

}
void Goomba::draw(){
     if(isActive){
          currentAnimation->animateSprite(0.15);
     }
}
void Goomba::initializeAnimationFrames(){
     //---------WALKING ANIMATION----------
     walkingAnimation.texture = textures.enemiesAnimations;
     walkingAnimation.bBox = &boundingBox;
     walkingAnimation.frames.push_back(SDL_Rect {1, 28, 16, 16});
     walkingAnimation.frames.push_back(SDL_Rect {18, 28, 16, 16});

     //---------DYING ANIMATION----------
     dyingAnimation.texture = textures.enemiesAnimations;
     dyingAnimation.bBox = &boundingBox;
     dyingAnimation.frames.push_back(SDL_Rect {39, 28, 16, 16});

}
void Goomba::onStaticEntityCollision(Vector2df penetration, Entity *e){
     // if(penetra  tion.y > 0){
     //      gravity = 0;
     // }else gravity = 800;

     if (penetration.x > 0) {
          direction = -1;
          // std::cout << ID << " : " << penetration.x  <<std::endl;
     }
     if(penetration.x < 0){
          direction = 1;
          // std::cout << ID << " : " << penetration.x  <<std::endl;
     }


     position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}

// void Goomba::onDynamicEntityCollision(Vector2df penetration, Entity* e){
//      // if(e->entityType == ENTITY_TYPE::PLAYER){
//      //      // if(penetration.y < 0 && e->velocity.y >= 0) isActive = false;
//      // }
// }
