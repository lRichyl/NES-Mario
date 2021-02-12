#include "player.h"
#include "global_variables.h"
#include "collision.h"
#include "vector2di.h"
#include <iostream>
#include <cmath>

Player::Player(){
	entityType = ENTITY_TYPE::PLAYER;
	isStatic = false;
	isActive = true;
	// sprite.texture = loadTexture("assets/textures/mario_animations.png");
	boundingBox.w = 64;
	boundingBox.h = 64;
	setClippingBox(98, 32, 12, 16); // This is not used when doing animated sprites
	initializeAnimationFrames();
	currentAnimation = &idleAnimation;
}

Player::~Player(){
	//Remember to always destroy the textures or it can cause a memory leak.
	//This will be done in the future in a texture manager.
	SDL_DestroyTexture(idleAnimation.texture);
	SDL_DestroyTexture(walkingAnimation.texture);
}
// bool updatePosition = false;
void Player::update(float deltaTime, SDL_Rect *camera){
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	position.y += 120 * deltaT;
	// if(updatePosition){
	// 	sprite.boundingBox.x = position.x - camera->x;
	// 	sprite.boundingBox.y = position.y - camera->y;
	// }

	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{
		position.y -= velocity.y * ydirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{
		position.y += velocity.y * ydirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		currentAnimation = &walkingAnimation;
		position.x -= velocity.x * xdirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		// currentAnimation = &walkingAnimation;
		position.x += velocity.x * xdirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_B ] )
	{
		position.y += velocity.x * -3 * deltaTime;
	}
	xdirection = 1;
	ydirection = 1;
	// position.y += (velocity.y * ydirection) * deltaTime;
	// position.x += (velocity.x * xdirection) * deltaTime;
	// std::cout << boundingBox.x << " , " << boundingBox.x << std::endl;
	updatePosition();
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	// if(currentAnimation->texture == nullptr){ std::cout << "NULL" << std::endl;}
	// std::cout << currentAnimation->boundingBox.x << " , " << currentAnimation->boundingBox.x << std::endl;
}

void Player::updatePosition(){
	boundingBox.x = position.x - CAMERA.bounds.x;
	boundingBox.y = position.y - CAMERA.bounds.y;
	// std::cout << boundingBox.x << " , " << boundingBox.x << std::endl;

}

void Player::draw(){
	// SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
	currentAnimation->animateSprite(0.08);
}


void Player::onCollision(Vector2df penetration){
		// std::cout << penetrationVector.x << " , " << penetrationVector.y << std::endl;
		// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}

void Player::initializeAnimationFrames(){
	/////IDLE ANIMATION///
	idleAnimation.texture    =  loadTexture("assets/textures/mario_animations.png");
	idleAnimation.bBox = &boundingBox;
	idleAnimation.frames.push_back(SDL_Rect {98, 32, 12, 16});
	/////WALKING ANIMATION///
	walkingAnimation.texture =  loadTexture("assets/textures/mario_animations.png");
	walkingAnimation.bBox = &boundingBox;
	walkingAnimation.frames.push_back(SDL_Rect {0, 32, 15, 16});
	walkingAnimation.frames.push_back(SDL_Rect {34, 32, 13, 16});
	walkingAnimation.frames.push_back(SDL_Rect {19, 32, 12, 16});
}
