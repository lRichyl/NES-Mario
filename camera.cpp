#include "camera.h"
#include "global_variables.h"

Camera::Camera(){
     resetCamera();
     xOffset = 0;
     yOffset = 0;
     scrollingSpeed = 500;
}

void Camera::resetCamera(){
     bounds.x = 0;
     xOffset = 0;
     yOffset = 0;
     bounds.y = 0;
     bounds.w = WINDOW_WIDTH;
     bounds.h = WINDOW_HEIGHT;
}


void Camera::updatePosition(){
     const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if( currentKeyStates[ SDL_SCANCODE_W ] )
	{
		yOffset -= scrollingSpeed * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_S ] )
	{
		yOffset += scrollingSpeed * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_A ] )
	{
		xOffset -= scrollingSpeed * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_D ] )
	{
		xOffset += scrollingSpeed * deltaT;
	}
	bounds.x = xOffset;
	bounds.y = yOffset;
	if(bounds.x < 0) {
		bounds.x = 0;
	}
	if(bounds.y < 0) {
		bounds.y = 0;
	}
}
