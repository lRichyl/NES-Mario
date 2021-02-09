#include <iostream>
#include "tile.h"


// Tile::Tile(int startingX , int startingY ){
	// x = startingX;
	// y = startingY;
// }
SDL_Texture* Tile::texture = nullptr;

void Tile::setTileSize(int newTileSize){
	isActive = true;
	if(Tile::texture == nullptr) Tile::texture = loadTexture("assets/textures/mario_blocks.png"); // THIS WILL BE MOVED TO A TEXTURE MANA
	sprite.texture = Tile::texture;
	sprite.boundingBox.w = tileSize;
	sprite.boundingBox.h = tileSize;
}


Tile::Tile(){
	setTileSize(Tile::tileSize);
	
};


void Tile::update(float deltaTime, SDL_Rect *camera){
	sprite.boundingBox.x = x - camera->x;
	sprite.boundingBox.y = y - camera->y;
}
void Tile::draw(){
	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
}


////////////////////////////////////////////////////////////
