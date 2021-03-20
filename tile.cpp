#include <iostream>
#include "tile.h"


// Tile::Tile(int startingX , int startingY ){
	// x = startingX;
	// y = startingY;
// }SDL_Texture* Tile::texture = nullptr;
int Tile::tileSize = 64;

Tile::Tile(){
	isActive = true;
	sprite.texture = texturesContainer.marioBlocks;
	// setTileSize(Tile::tileSize);
};

Tile::Tile(SDL_Texture *texture, SDL_Rect clippingBox, ENTITY_TYPE type, bool isStatic){
	sprite.texture = texture;
	setClippingBox(clippingBox.x, clippingBox.y, clippingBox.w, clippingBox.h);
	entityType = type;
}

void Tile::update(float deltaTime, SDL_Rect *camera){
	boundingBox.x = position.x - camera->x;
	boundingBox.y = position.y - camera->y;
}
void Tile::draw(){
	// sprite.animateSprite(0);
	SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &boundingBox );
}

void QuestionMarkTile::changeVariant(SDL_Event *e){
	int maxItemType = static_cast<int>(ITEM_TYPE::MAX);
	int minItemType = static_cast<int>(ITEM_TYPE::MIN);

	switch( e->key.keysym.sym ){
		case SDLK_e:{
			itemTypeCount++;
			if(itemTypeCount > maxItemType) itemTypeCount = minItemType;
		    	break;
	     }
	    case SDLK_q:{
		    itemTypeCount--;
		    if(itemTypeCount < minItemType) itemTypeCount = maxItemType;
		    break;
	    }
	}
	selectedItemType = itemTypeCount;
	setItemType(selectedItemType);

	// std::cout << itemTypeCount << std::endl;
}

void QuestionMarkTile::setItemType(int selectedItemType){
	switch(selectedItemType){
		case 0:{
			itemType = ITEM_TYPE::MUSHROOM;
			break;
		}
		case 1:{
			itemType = ITEM_TYPE::FIRE_FLOWER;
			break;
		}
		case 2:{
			itemType = ITEM_TYPE::STAR;
			break;
		}
		case 3:{
			itemType = ITEM_TYPE::EXTRA_LIFE;
			break;
		}
	}
}
