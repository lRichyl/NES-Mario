#include "scene.h"
#include "global_variables.h"
#include <iostream>


Scene::Scene(){
	CAMERA.resetCamera();
	// CAMERA.xOffset = 3 * Tile::tileSize;
	// CAMERA.yOffset = 3 * Tile::tileSize;
}

void Scene::updateScene(float deltaTime){
	CAMERA.updatePosition();
	layer0.update(deltaT, &CAMERA.bounds);
	layer1.update(deltaT, &CAMERA.bounds);
	layer2.update(deltaT, &CAMERA.bounds);
	layer3.update(deltaT, &CAMERA.bounds);
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
	CAMERA.resetCamera();
}
