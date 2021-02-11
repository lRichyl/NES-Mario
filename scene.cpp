#include "scene.h"
#include "global_variables.h"
#include <iostream>


Scene::Scene(){
	CAMERA.x = 0;
	CAMERA.y = 0;
	CAMERA.w = 1280;
	CAMERA.h = 720;
}
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
	CAMERA.x = x;
	CAMERA.y = y;
	if(CAMERA.x < 0) {
		CAMERA.x = 0;
	}
	if(CAMERA.y < 0) {
		CAMERA.y = 0;
	}
	layer0.update(deltaT, &CAMERA);
	layer1.update(deltaT, &CAMERA);
	layer2.update(deltaT, &CAMERA);
	layer3.update(deltaT, &CAMERA);
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
	CAMERA.x = 0;
	CAMERA.y = 0;
	x = 0;
	y = 0;
}
