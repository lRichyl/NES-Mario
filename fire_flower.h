#pragma once
#include "entity.h"


struct FireFlower : public Entity{
     enum FireFlowerState{
          SPAWNING,
          NORMAL
     };

     // FireFlower();
     FireFlower(Vector2df position, int finalSpawningPosition);

     FireFlowerState state = SPAWNING;
     ITEM_TYPE type = ITEM_FIRE_FLOWER;

     int finalSpawningPosition = 0;
     int spawningSpeed = 80;

     Sprite sprite;

     void update(float deltaTime, Camera *camera) override;
	void draw() override;
     void onStaticEntityCollision(Vector2df penetration,Entity* e)override;
     void onDynamicEntityCollision(Vector2df,Entity*)override;


     Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new FireFlower(*this);}
};
