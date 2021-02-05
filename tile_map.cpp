#include "tile_map.h"
#include <cmath>

TileMap::TileMap(){
	entities.resize((unsigned int)(levelWidth/tileWidth));
	for(unsigned int j = 0; j < entities.size(); j++){
		entities[j].resize(levelHeight/tileHeight, nullptr);
	}
}

bool TileMap::addEntityByPosition(Entity *e){	
	int xTile = (e->x) / (float)tileWidth;
	int yTile = (e->y) / (float)tileHeight;
	
	if(entities[xTile][yTile] == nullptr){
		// std::cout << windowWidth << std::endl;
		entities[xTile][yTile] = e;
		e->x = xTile * tileWidth;
		e->y = yTile * tileHeight;
		// e->update(deltaT);//this is done once to set the position of the bounding box to the actual position of the texture.
		return true;
	}
	return false;
		
}

// bool TileMap::addEntityByTile(Entity *e){	
	// int xTile = e->x;
	// int yTile = e->y;
	
	// if(entities[xTile][yTile] == nullptr){		
		// entities[xTile][yTile] = e;
		// e->x = xTile * tileWidth;
		// e->y = yTile * tileHeight;
		// e->update(deltaT);//this is done once to set the position of the bounding box to the actual position of the texture.
		// return true;
	// }
	// return false;	
// }
bool TileMap::addEntityOnTile(int xTile, int yTile, Entity *e){	
	if(entities[xTile][yTile] == nullptr){
		entities[xTile][yTile] = e;		
		return true;
	}
	return false;	
}

void TileMap::draw(){
	// int xSize = levelWidth / tileWidth;
	// int ySize = levelHeight / tileHeight;
	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){	
				// if(entities[i][j]->isStatic){
					// entities[i][j]->sprite.boundingBox.x = i * tileWidth - camera->x;
					// entities[i][j]->sprite.boundingBox.y = j * tileHeight - camera->y;
				// }
				entities[i][j]->draw();	
			}				
		}
	}
}

void TileMap::update(float deltaT, SDL_Rect *camera){
	// int xSize = levelWidth / tileWidth;
	// int ySize = levelHeight / tileHeight;
	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){				
				entities[i][j]->update(deltaT, camera);
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
	for(unsigned int i = 0; i < entities.size() ; i++){
		for(unsigned int j = 0; j < entities[i].size(); j++){
			if(entities[i][j] != nullptr){				
				delete entities[i][j];
			}	
		}
	}
}