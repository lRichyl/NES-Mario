#include "mushroom.h"
#include "global_variables.h"
#include <iostream>

//
// Mushroom::Mushroom(){
//      isStatic = false;
//      sprite.texture = texturesContainer.items;
//      sprite.bBox = &boundingBox;
//      sprite.frames.push_back(SDL_Rect{0, 0, 16, 16});
//      velocity.x = 90;
//      updatePosition();
// }

Mushroom::Mushroom(Vector2df p, int finalSpawningPosition){
     isStatic = false;
     sprite.texture = texturesContainer.items;
     sprite.bBox = &boundingBox;
     sprite.frames.push_back(SDL_Rect{0, 0, 16, 16});

     entityType = ENTITY_TYPE::MUSHROOM;
     this->position = p;
     this->finalSpawningPosition = finalSpawningPosition;
     velocity.x = 90;
     updatePosition();
}

void Mushroom::update(float deltaTime, Camera *camera){
     // localCamera = *camera;
     if(state == MushroomState::SPAWNING){
          position.y -= spawningSpeed * deltaTime;
          if(position.y <= finalSpawningPosition) state = MushroomState::NORMAL;

     }else if(state == MushroomState::NORMAL){
          position.x += direction * velocity.x * deltaTime;
          velocity.y += gravity *deltaTime;
          position.y += velocity.y;
     }

     updatePosition();
}

void Mushroom::draw(){
     sprite.animateSprite(0);
}

// void Mushroom::updatePosition(){
//      boundingBox.x = position.x - localCamera.bounds.x;
// 	boundingBox.y = position.y - localCamera.bounds.y;
// }

void Mushroom::onStaticEntityCollision(Vector2df penetration, Entity *e){

     if(state == MushroomState::NORMAL){

          if(penetration.y > 0) velocity.y = 0;
          if(penetration.x > 0) direction = -1;
          if(penetration.x < 0) direction = 1;


          position.x -= penetration.x;
          position.y -= penetration.y;

          updatePosition();
     }
}

void Mushroom::onDynamicEntityCollision(Vector2df penetration ,Entity *e){

}
