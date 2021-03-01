#include <iostream>
#include "tile.h"


// Tile::Tile(int startingX , int startingY ){
	// x = startingX;
	// y = startingY;
// }SDL_Texture* Tile::texture = nullptr;
int Tile::tileSize = 64;

void Tile::setTileSize(int newTileSize){
	isActive = true;
	texture = textures.marioBlocks;
	// if(Tile::texture == nullptr){
	// 	Tile::texture = loadTexture("assets/textures/mario_blocks.png"); // THIS WILL BE MOVED TO A TEXTURE MANA
	// }
	sprite.texture = texture;
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
//////////////////////////////////////////////////////////
QuestionMark::QuestionMark(){
     entityType = ENTITY_TYPE::QUESTIONMARK;
     isStatic = true;
     // boundingBox.w = Tile::tileSize;
	// boundingBox.h = Tile::tileSize;
     initAnimation();
}

void QuestionMark::initAnimation(){
     blockUnused.texture = textures.marioBlocks;
     blockUnused.bBox = &boundingBox;
     blockUnused.frames.push_back(SDL_Rect {384, 0, 16, 16});
     blockUnused.frames.push_back(SDL_Rect {400, 0, 16, 16});
     blockUnused.frames.push_back(SDL_Rect {416, 0, 16, 16});

     blockUsed.texture = textures.marioBlocks;
     blockUsed.bBox = &boundingBox;
     blockUsed.frames.push_back(SDL_Rect {432, 0, 16, 16});
}

void QuestionMark::update(float deltaTime, SDL_Rect *camera){
     boundingBox.x = position.x - camera->x;
	boundingBox.y = position.y - camera->y;
	std::cout << &boundingBox << std::endl;
	std::cout << blockUnused.bBox << std::endl;
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;
}

void QuestionMark::draw(){
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;
     blockUnused.animateSprite(0.5);
	// SDL_RenderCopy( renderer, textures.marioBlocks, &blockUnused.frames[0], &boundingBox );
}
