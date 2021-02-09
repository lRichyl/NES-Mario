#include "scene.h"
#include <iostream>


// void Scene::setScale(float xScale, float yScale){
	// background.xScale = xScale;
	// background.yScale = yScale;
	// background.scaleDimensions();
	// below.xScale = xScale;
	// below.yScale = yScale;
	// below.scaleDimensions(),
	// collideable.xScale = xScale;
	// collideable.yScale = yScale;
	// collideable.scaleDimensions();
	// above.xScale = xScale;
	// above.yScale = yScale;
	// above.scaleDimensions();
// }
static float x = 0;// This variables are temporary. Should be in the camera class
static float y = 0;
void Scene::updateScene(float deltaTime){
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if( currentKeyStates[ SDL_SCANCODE_W ] )
	{
		y -= 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_S ] )
	{
		y += 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_A ] )
	{
		x -= 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_D ] )
	{
		x += 60 * deltaT;
	}
	camera.x = x;
	camera.y = y;
	if(camera.x < 0) {
		camera.x = 0;
	}
	if(camera.y < 0) {
		camera.y = 0;
	}
	layer0.update(deltaT, &camera);
	layer1.update(deltaT, &camera);
	layer2.update(deltaT, &camera);
	layer3.update(deltaT, &camera);
}

void Scene::checkCollisions(){
	collisionManager.checkCollisions(&layer2);
}

void Scene::drawScene(){
	layer0.draw();
	// SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD); //This will be used later for lighting.
	layer1.draw();
	layer2.draw();
	layer3.draw();
}

void Scene::unloadEntities(){
	layer0.emptyTilemap();
	layer1.emptyTilemap();
	layer2.emptyTilemap();
	layer3.emptyTilemap();
}

void Scene::resetCamera(){
	camera.x = 0;
	camera.y = 0;
	x = 0;
	y = 0;
}
