#include "entity.h"
#include "tile.h"
#include <iostream>

int Entity::IDcount = 0;

Entity::Entity(){
	IDcount++;
	ID = IDcount;
	boundingBox.h = Tile::tileSize;
     boundingBox.w = Tile::tileSize;
}

// void Entity::update(float deltaTime, Camera *camera){
//
// }
// void Entity::draw(){
//
// }



void Entity::setTileSize(int tileSize){
	boundingBox.w = tileSize;
	boundingBox.h = tileSize;
}

void Entity::updatePosition(){
	boundingBox.x = position.x - localCamera.bounds.x;
	boundingBox.y = position.y - localCamera.bounds.y;
}

void Entity::updateLocalCamera(Camera camera){
	localCamera = camera;
}

void Entity::setInactiveIfOutsideOfCameraBounds(){
	if(entityType != ENTITY_TYPE::PLAYER && !isDestroyed){
		if(isActive){
			if(boundingBox.y + Tile::tileSize <= 0 || boundingBox.y > localCamera.bounds.h || boundingBox.x + Tile::tileSize <= 0 || boundingBox.x > localCamera.bounds.w){
				isActive = false;
			}

		}else{
			updatePosition();
			if(boundingBox.y  >= 0 && boundingBox.y + Tile::tileSize < localCamera.bounds.h && boundingBox.x  >= 0 && boundingBox.x + Tile::tileSize < localCamera.bounds.w ){
				isActive = true;
			}
		}


		// else if (boundingBox.x + Tile::tileSize < 0 || boundingBox.x > localCamera.bounds.w){
		// 	isActive = false;
		// else isActive = true;
	}
}
