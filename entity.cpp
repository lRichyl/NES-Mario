#include "entity.h"
#include "tile.h"

int Entity::IDcount = 0;

Entity::Entity(){
	ID = IDcount;
	IDcount++;
	boundingBox.h = Tile::tileSize;
     boundingBox.w = Tile::tileSize;
}

// void Entity::update(float deltaTime, Camera *camera){
//
// }
// void Entity::draw(){
//
// }

void Entity::setClippingBox(int x, int y, int w, int h){
	clippingBox.x = x;
	clippingBox.y = y;
	clippingBox.w = w;
	clippingBox.h = h;
}

void Entity::setTileSize(int tileSize){
	boundingBox.w = tileSize;
	boundingBox.h = tileSize;
}

void Entity::updatePosition(){
	boundingBox.x = position.x - localCamera.bounds.x;
	boundingBox.y = position.y - localCamera.bounds.y;
}
