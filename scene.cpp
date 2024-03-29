#include "scene.h"
#include "global_variables.h"
#include <iostream>


Scene::Scene(){
	camera.resetCamera();
	// CAMERA.xOffset = 3 * Tile::tileSize;
	// CAMERA.yOffset = 3 * Tile::tileSize;
}

void Scene::updateScene(float deltaTime){
	camera.updatePosition();
	layer0.update(deltaTime, &camera);
	layer1.update(deltaTime, &camera);
	layer2.update(deltaTime, &camera);
	layer3.update(deltaTime, &camera);
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
	camera.resetCamera();
}
