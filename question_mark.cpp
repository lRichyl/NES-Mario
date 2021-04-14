#include "question_mark.h"
#include "global_variables.h"
#include "dynamic_entities.h"
#include <iostream>

QuestionMark::QuestionMark(){
     entityType = ENTITY_QUESTIONMARK;
     isStatic = true;
     isActive = true;

     initAnimation();
     initSounds();
	currentAnimation = &blockUnused;

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

void QuestionMark::update(float deltaTime, Camera *camera){
	if(state == QuestionMarkState::NORMAL){
		currentAnimation = &blockUnused;

	}
	else if(state == QuestionMarkState::DISABLED){
	 	currentAnimation = &blockUsed;
          bumpingSound.play();

          // if(!pushBlock && position.y == originalPosition) return;
          if(pushBlock){
               if(position.y > maxYmovement) position.y -= speed;
               else pushBlock = false;
          }else{
               if(position.y < originalPosition) position.y += speed;
          }

          if(!pushBlock && position.y == originalPosition && spawnItem){
               spawnItem = false;

               switch(itemType){
                    case ITEM_MUSHROOM:{
                         Mushroom *m = new Mushroom(position, position.y - Tile::tileSize);
                         tilemapToSpawnItemsOn->dynamicEntities.push_back(m);

                         break;
                    }
                    case ITEM_FIRE_FLOWER:{
                         FireFlower *f = new FireFlower(position, position.y - Tile::tileSize);
                         tilemapToSpawnItemsOn->dynamicEntities.push_back(f);

                         break;
                    }
                    default:
                    std::cout << "NO TYPE" << std::endl;


               }
          }
          // std::cout << static_cast<int>(itemType) << std::endl;

	}




     updatePosition();
     currentAnimation->update(0.5);
}

void QuestionMark::draw(){

     currentAnimation->animateSprite();
}

void QuestionMark::initParameters(){
     maxYmovement = position.y - 16;
	originalPosition = position.y;
}

void QuestionMark::initSounds(){
     bumpingSound.channel = 4;
     bumpingSound.sound = soundsContainer.bump;
}
