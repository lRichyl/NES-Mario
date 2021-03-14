#include <iostream>
#include "tile.h"


// Tile::Tile(int startingX , int startingY ){
	// x = startingX;
	// y = startingY;
// }SDL_Texture* Tile::texture = nullptr;
int Tile::tileSize = 64;

void Tile::setTileSize(int newTileSize){
	isActive = true;
	texture = texturesContainer.marioBlocks;
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
///////////////////////QUESTION MARK TILE///////////////////////////////////
QuestionMark::QuestionMark(){
     entityType = ENTITY_TYPE::QUESTIONMARK;
     isStatic = true;
     initAnimation();
}

void QuestionMark::initAnimation(){
     blockUnused.texture = texturesContainer.marioBlocks;
     blockUnused.bBox = &boundingBox;
     blockUnused.frames.push_back(SDL_Rect {384, 0, 16, 16});
     blockUnused.frames.push_back(SDL_Rect {400, 0, 16, 16});
     blockUnused.frames.push_back(SDL_Rect {416, 0, 16, 16});

     blockUsed.texture = texturesContainer.marioBlocks;
     blockUsed.bBox = &boundingBox;
     blockUsed.frames.push_back(SDL_Rect {432, 0, 16, 16});
}

void QuestionMark::update(float deltaTime, SDL_Rect *camera){
     boundingBox.x = position.x - camera->x;
	boundingBox.y = position.y - camera->y;
	std::cout << tilemapToSpawnItemsOn << std::endl;
}

void QuestionMark::draw(){
     blockUnused.animateSprite(0.5);
}
