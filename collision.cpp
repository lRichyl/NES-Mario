#include "collision.h"
#include <iostream>

void CollisionManager::minkowskiDifference(SDL_Rect b1, SDL_Rect b2){
	int mdtop   =  b1.y - (b2.y + b2.h);
	int mdbott  =  (b1.y + b1.h) - b2.y;
	int mdleft  =  b1.x - (b2.x + b2.w);
	int mdright =  (b1.x + b1.w) - b2.x;

	if(mdright >= 0 && mdleft <= 0 && mdtop <= 0 && mdbott >= 0){
		std::cout << "collided" << std::endl;
	}
}

void CollisionManager::checkCollisions(TileMap *collisionLayer){
	for(unsigned int k = 0; k < collisionLayer->dynamicEntities.size(); k++){
		if(collisionLayer->dynamicEntities[k] != nullptr){
			// std::cout << "mario" << std::endl;
			for(unsigned int i = 0; i < collisionLayer->entities.size() ; i++){
				for(unsigned int j = 0; j < collisionLayer->entities[i].size(); j++){
					if(collisionLayer->entities[i][j] != nullptr){
					minkowskiDifference(collisionLayer->dynamicEntities[k]->sprite.boundingBox,collisionLayer->entities[i][j]->sprite.boundingBox);
					}
				}
			}
		}
	}
}
