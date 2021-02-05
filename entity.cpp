#include "entity.h"

Entity::Entity(){
	
}

void Entity::update(float deltaTime, SDL_Rect *camera){
	
}
void Entity::draw(){
	
}

void Entity::setClippingBox(int x, int y, int w, int h){
	clippingBox.x = x;
	clippingBox.y = y;
	clippingBox.w = w;
	clippingBox.h = h;
}

void Entity::setTileSize(int tileSize){
	sprite.boundingBox.w = tileSize;
	sprite.boundingBox.h = tileSize;
}

