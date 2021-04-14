#include "fire_flower.h"
#include "global_variables.h"
#include "player.h"


FireFlower::FireFlower(Vector2df position, int finalSpawningPosition){
     isStatic = false;
     sprite.texture = texturesContainer.items;
     sprite.bBox = &boundingBox;
     sprite.frames.push_back(SDL_Rect{0, 32, 16, 16});
     sprite.frames.push_back(SDL_Rect{16, 32, 16, 16});
     sprite.frames.push_back(SDL_Rect{32, 32, 16, 16});
     sprite.frames.push_back(SDL_Rect{48, 32, 16, 16});

     entityType = ENTITY_ITEM;
     this->position = position;
     this->finalSpawningPosition = finalSpawningPosition;
     updatePosition();
}

void FireFlower::update(float deltaTime, Camera *camera){
     // localCamera = *camera;
     if(state == FireFlowerState::SPAWNING){
          position.y -= spawningSpeed * deltaTime;
          if(position.y <= finalSpawningPosition) state = FireFlowerState::NORMAL;

     }

     updatePosition();
     sprite.update(0.08);
}

void FireFlower::draw(){
     sprite.animateSprite();
}

void FireFlower::onStaticEntityCollision(Vector2df penetration,Entity* e){
     if(state == FireFlowerState::NORMAL){

          if(penetration.y > 0) velocity.y = 0;


          position.x -= penetration.x;
          position.y -= penetration.y;

          updatePosition();
     }
}
void FireFlower::onDynamicEntityCollision(Vector2df penetration ,Entity *e){
     // if(e->entityType == ENTITY_TYPE::PLAYER){
     //      isActive = false;
     //      Player *p = dynamic_cast<Player*>(e);
     //      p->state = p->PICKING_FIRE;
     // }
}
