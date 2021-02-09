#include "player.h"
#include "global_variables.h"
#include <iostream>

void Player::update(float deltaTime, SDL_Rect *camera){
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		if( currentKeyStates[ SDL_SCANCODE_UP ] )
		{
			position.y -= velocity.y * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
		{
			position.y += velocity.y * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
		{
			position.x -= velocity.x * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
		{
			position.x += velocity.x * deltaTime;
		}
		sprite.boundingBox.x = position.x - camera->x;
		sprite.boundingBox.y = position.y - camera->y;

}

void Player::draw(){

	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
}
