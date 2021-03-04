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
}

void Goomba::update(float deltaTime, SDL_Rect *camera){
     position.x += direction * speed * deltaTime;
     position.y += 800 * deltaTime;
     // std::cout << "goomba test" << std::endl;
     boundingBox.x = position.x - CAMERA.bounds.x;
	boundingBox.y = position.y - CAMERA.bounds.y;
}
void Goomba::updatePosition(){
	boundingBox.x = position.x - CAMERA.bounds.x;
	boundingBox.y = position.y - CAMERA.bounds.y;
	// std::cout << boundingBox.x << " , " << boundingBox.x << std::endl;

}
void Goomba::draw(){
     currentAnimation->animateSprite(0.15);
}
void Goomba::initializeAnimationFrames(){
     walkingAnimation.texture = textures.enemiesAnimations;
     walkingAnimation.bBox = &boundingBox;
     walkingAnimation.frames.push_back(SDL_Rect {1, 28, 16, 16});
     walkingAnimation.frames.push_back(SDL_Rect {18, 28, 16, 16});

     dyingAnimation.texture = textures.enemiesAnimations;
     dyingAnimation.bBox = &boundingBox;
     dyingAnimation.frames.push_back(SDL_Rect {39, 28, 16, 16});

}
void Goomba::onCollision(Vector2df penetration){
     std::cout << "collision" << std::endl;

     if(penetration.x < 0) direction = 1;
     else if (penetration.x > 0) direction = -1;

     position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}
