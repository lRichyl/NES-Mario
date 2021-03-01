// #include "question_mark.h"
// #include "global_variables.h"
// #include "tile.h"

// QuestionMark::QuestionMark(){
//      entityType = ENTITY_TYPE::QUESTIONMARK;
//      isStatic = true;
//      boundingBox.w = Tile::tileSize;
// 	boundingBox.h = Tile::tileSize;
//      initAnimation();
// }
//
// void QuestionMark::initAnimation(){
//      blockUnused.texture = textures.marioBlocks;
//      blockUnused.bBox = &boundingBox;
//      blockUnused.frames.push_back(SDL_Rect {384, 0, 16, 16});
//      blockUnused.frames.push_back(SDL_Rect {400, 0, 16, 16});
//      blockUnused.frames.push_back(SDL_Rect {416, 0, 16, 16});
//
//      blockUsed.texture = textures.marioBlocks;
//      blockUsed.bBox = &boundingBox;
//      blockUsed.frames.push_back(SDL_Rect {432, 0, 16, 16});
// }
//
// void QuestionMark::update(float deltaTime, SDL_Rect *camera){
//      boundingBox.x = position.x - CAMERA.bounds.x;
// 	boundingBox.y = position.y - CAMERA.bounds.y;
// }
//
// void QuestionMark::draw(){
//      blockUnused.animateSprite(0.5);
//
// }
