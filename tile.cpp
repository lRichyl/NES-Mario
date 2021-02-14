#include <iostream>
#include "tile.h"


// Tile::Tile(int startingX , int startingY ){
	// x = startingX;
	// y = startingY;
// }
SDL_Texture* Tile::texture = nullptr;
int Tile::tileSize = 64;

void Tile::setTileSize(int newTileSize){
	isActive = true;
	if(Tile::texture == nullptr){
		Tile::texture = loadTexture("assets/textures/mario_blocks.png"); // THIS WILL BE MOVED TO A TEXTURE MANA
	}
	sprite.texture = Tile::texture;
	boundingBox.w = tileSize;
	boundingBox.h = tileSize;
}


Tile::Tile(){
	setTileSize(Tile::tileSize);

};


void Tile::update(float deltaTime, SDL_Rect *camera){
	boundingBox.x = position.x - camera->x;
	boundingBox.y = position.y - camera->y;
}
void Tile::draw(){
	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &boundingBox );
}


////////////////////////////////////////////////////////////
