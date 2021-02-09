#include "collision.h"
#include <iostream>

bool CollisionManager::AABBCollision(SDL_Rect b1, SDL_Rect b2){
	if (b1.x < b2.x + b2.w &&
		b1.x + b1.w > b2.x &&
		b1.y < b2.y + b2.h &&
		b1.y + b1.h > b2.y) {
		
		return true;
	}else 
		return false;
}

void CollisionManager::checkCollisions(TileMap *collisionLayer){
	for(unsigned int i = 0; i < collisionLayer->entities.size() ; i++){
		for(unsigned int j = 0; j < collisionLayer->entities[i].size(); j++){
			if(collisionLayer->entities[i][j] != nullptr){
				
			}				
		}
	}
}