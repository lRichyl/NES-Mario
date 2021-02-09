#include "player.h"
#include "global_variables.h"
#include <iostream>

void Player::update(float deltaTime, SDL_Rect *camera){
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
		if( currentKeyStates[ SDL_SCANCODE_UP ] )
		{
			y -= velocity * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
		{
			y += velocity * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
		{
			x -= velocity * deltaTime;
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
		{
			x += velocity * deltaTime;
		}
		sprite.boundingBox.x = x - camera->x;
		sprite.boundingBox.y = y - camera->y;

}

void Player::draw(){

	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
}
