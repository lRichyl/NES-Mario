#include "player.h"
#include "global_variables.h"
#include "collision.h"
#include "vector2di.h"
#include <iostream>
#include <cmath>

Player::~Player(){
	//Remember to always destroy the textures or it can cause a memory leak.
	//This will be done in the future in a texture manager.
	SDL_DestroyTexture(sprite.texture);
}
// bool updatePosition = false;
void Player::update(float deltaTime, SDL_Rect *camera){
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
		position.x -= velocity.x * xdirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
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
	updatePosition();
}

void Player::updatePosition(){
	sprite.boundingBox.x = position.x - CAMERA.x;
	sprite.boundingBox.y = position.y - CAMERA.y;
}

void Player::draw(){
	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
}


void Player::onCollision(Vector2df penetration){
		// std::cout << penetrationVector.x << " , " << penetrationVector.y << std::endl;
	position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}
