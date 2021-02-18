#include "tile_map.h"
#include <cmath>

TileMap::TileMap(){
	entities.resize((unsigned int)(levelWidth/tileWidth));
	for(unsigned int i = 0; i < entities.size(); i++){
		entities[i].resize(levelHeight/tileHeight, nullptr);
	}
	// dynamicEntities.clear();
}

bool TileMap::addEntityOnTile(int xTile, int yTile, Entity *e){
	if(entities[xTile][yTile] == nullptr){
		entities[xTile][yTile] = e;
		return true;
	}
	return false;
}

void TileMap::draw(){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){
			dynamicEntities[i]->draw();

		}
	}

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				entities[i][j]->draw();
			}
		}
	}
}

void TileMap::update(float deltaT, SDL_Rect *camera){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){

			dynamicEntities[i]->update(deltaT, camera);
			// std::cout << dynamicEntities[i]->boundingBox.x << " , " << dynamicEntities[i]->boundingBox.y << std::endl;

			// std::cout << "Mario" << std::endl;
		}
	}

	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){
				entities[i][j]->update(deltaT, camera);
			}
		}
	}
}

void TileMap::emptyTilemap(){
	for(unsigned int i = 0; i < dynamicEntities.size(); i++){
		if(dynamicEntities[i] != nullptr){
			delete dynamicEntities[i];
			dynamicEntities[i] = nullptr;
		}
	}
	dynamicEntities.clear();

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
