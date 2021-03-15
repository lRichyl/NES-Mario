#include "question_mark.h"
#include "global_variables.h"
#include <iostream>

QuestionMark::QuestionMark(){
     entityType = ENTITY_TYPE::QUESTIONMARK;
     isStatic = false;
     isActive = true;

     initAnimation();
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

void QuestionMark::update(float deltaTime, SDL_Rect *camera){
	if(state == QuestionMarkState::NORMAL){
		currentAnimation = &blockUnused;
          std::cout << maxYmovement << " , " << position.y <<  std::endl;

	}
	else if(state == QuestionMarkState::DISABLED){
	 	currentAnimation = &blockUsed;
		if(pushBlock){
			if(position.y > maxYmovement) position.y -= speed;
		}

	}




     boundingBox.x = position.x - camera->x;
	boundingBox.y = position.y - camera->y;
}

void QuestionMark::draw(){

     currentAnimation->animateSprite(0.5);
}

void QuestionMark::initParameters(){
     maxYmovement = position.y - 16;
	originalPosition = position.y;
}
