#include "tile_map.h"
#include "dynamic_entities.h"
#include "player.h"
#include <cmath>

TileMap::TileMap(){
	entities.resize((unsigned int)(levelWidth/tileWidth));
	for(unsigned int i = 0; i < entities.size(); i++){
		entities[i].resize(levelHeight/tileHeight, nullptr);
	}
	// dynamicEntities.clear();
}

void TileMap::copyTileMap(const TileMap *tileMap){
	for(unsigned int i = 0; i < tileMap->entities.size(); i++){
		for(unsigned int j = 0; j < tileMap->entities[i].size(); j++){
			if(tileMap->entities[i][j] != nullptr){
				entities[i][j] = tileMap->entities[i][j]->clone();

			}
		}
	}
}

bool TileMap::addEntityOnTile(int xTile, int yTile, Entity *e){
	if(entities[xTile][yTile] == nullptr){
		entities[xTile][yTile] = e;
		return true;
	}
	return false;
}

bool TileMap::updateOnlyPlayer = false;

void TileMap::draw(){
	// for(unsigned int i = 0; i < dynamicEntities.size(); i++){
	// 	if(dynamicEntities[i] != nullptr){
	// 		if(dynamicEntities[i]->isActive && !dynamicEntities[i]->isDestroyed)
	// 			dynamicEntities[i]->draw();
	//
	// 	}
	// }

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				if(entities[i][j]->isActive && !entities[i][j]->isDestroyed)
					entities[i][j]->draw();
			}
		}
	}
}

void TileMap::update(float deltaT, Camera *camera){
	// if(updateOnlyPlayer){
	// 	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
	// 		if(dynamicEntities[i] != nullptr && dynamicEntities[i]->entityType == ENTITY_PLAYER){
	// 			dynamicEntities[i]->update(deltaT, camera);
	// 			dynamicEntities[i]->currentAnimation->update();
	// 			// std::cout << dynamicEntities[i]->boundingBox.x << " , " << dynamicEntities[i]->boundingBox.y << std::endl;
	//
	// 			// std::cout << "Mario" << std::endl;
	// 		}
	// 	}
	// }else{
		// for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		// 	if(dynamicEntities[i] != nullptr){
		// 		dynamicEntities[i]->updateLocalCamera(*camera);
		// 		dynamicEntities[i]->setInactiveIfOutsideOfCameraBounds();
		// 		if(dynamicEntities[i]->isActive && !dynamicEntities[i]->isDestroyed)
		// 		dynamicEntities[i]->update(deltaT, camera);
		// 		dynamicEntities[i]->currentAnimation->update();
		// 		// std::cout << dynamicEntities[i]->boundingBox.x << " , " << dynamicEntities[i]->boundingBox.y << std::endl;
		//
		// 		// std::cout << "Mario" << std::endl;
		// 	}
		// }

		for(unsigned int i = 0; i < entities.size() ; i++){
			for(unsigned int j = 0; j < entities[i].size(); j++){
				if(entities[i][j] != nullptr){
					entities[i][j]->updateLocalCamera(*camera);
					if(entities[i][j]->isActive  && !entities[i][j]->isDestroyed)
						entities[i][j]->update(deltaT, camera);
						// entities[i][j]->currentAnimation->update();
					// std::cout << entities[i][j]->boundingBox.x << " , " << entities[i][j]->boundingBox.y << std::endl;

				}
			}
		}

	// }
}

void TileMap::emptyTilemap(){


	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				delete entities[i][j];
				entities[i][j] = nullptr;
			}
		}
	}
}

int TileMap::getXTile(float xPosition){
	int xTile = (xPosition) / (float)tileWidth;
	return xTile;
}
int TileMap::getYTile(float yPosition){
	// int yTile = (yPosition) / (float)tileHeight;
	// return yTile;
	float yTile;
	if(yPosition < 0){
		yTile = ceil((yPosition) / (float)tileHeight);
	}else{
		yTile = floor((yPosition) / (float)tileHeight);
	}
	return (int)yTile;
}

TileMap::~TileMap(){
	// for(unsigned int i = 0; i < dynamicEntities.size(); i++){
	// 	if(dynamicEntities[i] != nullptr){
	// 		delete dynamicEntities[i];
	// 	}
	// }

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				delete entities[i][j];
			}
		}
	}
}
static void setDynamicEntityPosition(Entity* tileEntity, Entity* d, Camera *camera){
	d->position.x = tileEntity->position.x - camera->bounds.x;
	d->position.y = tileEntity->position.y - camera->bounds.y;
	d->updatePosition();
}
void CollisionTileMap::copyTileMap(const TileMap *tileMap, Camera *camera){
	for(unsigned int i = 0; i < tileMap->entities.size(); i++){
		for(unsigned int j = 0; j < tileMap->entities[i].size(); j++){
			Entity *e = tileMap->entities[i][j];
			if(e != nullptr){
				if(e->isStatic ){
					if(e->entityType == ENTITY_QUESTIONMARK){
						QuestionMark *q = new QuestionMark();
						QuestionMarkTile *tile = dynamic_cast<QuestionMarkTile*>(e);
						setDynamicEntityPosition(e, q, camera);
						q->initParameters();
						q->itemType = tile->itemType;
						q->tilemapToSpawnItemsOn = this;
						entities[i][j] = q;
					}else
						entities[i][j] = e->clone();
				}else{

					switch(e->entityType){
						case ENTITY_PLAYER:
						{
							Player *p = new Player();

							setDynamicEntityPosition(e, p, camera);

							dynamicEntities.push_back(p);
							break;
						}
						case ENTITY_GOOMBA:
						{
							Goomba *g = new Goomba();
							setDynamicEntityPosition(e, g, camera);

							dynamicEntities.push_back(g);
							break;
						}
					}
				}
				// if(e->entityType == ENTITY_TYPE::PLAYER){
				// 	Player *p = new Player();
				// 	setDynamicEntityPosition(e, p);
				//
				// 	level->layer2.dynamicEntities.push_back(p);
				//
				// } else if(e->entityType == ENTITY_TYPE::GOOMBA){
				// 	Goomba *g = new Goomba();
				// 	setDynamicEntityPosition(e, g);
				//
				// 	level->layer2.dynamicEntities.push_back(g);
				//
				// }
			}
		}
	}
}

void CollisionTileMap::update(float deltaT, Camera *camera){
	if(updateOnlyPlayer){
		for(unsigned int i = 0; i < dynamicEntities.size(); i++){
			if(dynamicEntities[i] != nullptr ){
				if(!dynamicEntities[i]->isDestroyed){
					dynamicEntities[i]->updateLocalCamera(*camera);
					if(dynamicEntities[i]->entityType == ENTITY_PLAYER){
						dynamicEntities[i]->update(deltaT, camera);
						dynamicEntities[i]->currentAnimation->update();
					}else{
						dynamicEntities[i]->updatePosition();
					}
				}
			}
		}
	}else{
		for(unsigned int i = 0; i < dynamicEntities.size(); i++){
			if(dynamicEntities[i] != nullptr){
				dynamicEntities[i]->updateLocalCamera(*camera);
				dynamicEntities[i]->setInactiveIfOutsideOfCameraBounds();
				if(dynamicEntities[i]->isActive && !dynamicEntities[i]->isDestroyed)
				dynamicEntities[i]->update(deltaT, camera);
				dynamicEntities[i]->currentAnimation->update();
				// std::cout << dynamicEntities[i]->boundingBox.x << " , " << dynamicEntities[i]->boundingBox.y << std::endl;

				// std::cout << "Mario" << std::endl;
			}
		}
	}
	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				entities[i][j]->updateLocalCamera(*camera);
				if(entities[i][j]->isActive  && !entities[i][j]->isDestroyed)
					entities[i][j]->update(deltaT, camera);
					// entities[i][j]->currentAnimation->update();
				// std::cout << entities[i][j]->boundingBox.x << " , " << entities[i][j]->boundingBox.y << std::endl;

			}
		}
	}
}

void CollisionTileMap::draw(){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){
			if(dynamicEntities[i]->isActive && !dynamicEntities[i]->isDestroyed)
				dynamicEntities[i]->draw();

		}
	}

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				if(entities[i][j]->isActive && !entities[i][j]->isDestroyed)
					entities[i][j]->draw();
			}
		}
	}
}
void CollisionTileMap::emptyTilemap(){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){
			delete dynamicEntities[i];
			dynamicEntities[i] = nullptr;
		}
	}
	dynamicEntities.clear();
}

CollisionTileMap::~CollisionTileMap(){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){
			delete dynamicEntities[i];
		}
	}

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				delete entities[i][j];
			}
		}
	}
}
