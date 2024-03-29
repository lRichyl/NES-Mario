#pragma once
#include "entity.h"
#include "camera.h"
#include "vector2df.h"

struct Mushroom : public Entity{
     enum MushroomState{
          SPAWNING,
          NORMAL
     };
     MushroomState state = SPAWNING;
     ITEM_TYPE type = ITEM_MUSHROOM;   

     // Mushr.oom();
     Mushroom(Vector2df position, int finalSpawningPosition);

     int finalSpawningPosition = 0;
     int spawningSpeed = 80;
     int normalSpeed = 50;
     int direction = 1;
     int gravity = 50;

     // Camera localCamera;

     Sprite sprite;

     // void updatePosition();
     void onStaticEntityCollision(Vector2df,Entity*)override;
	void onDynamicEntityCollision(Vector2df,Entity*)override;
     void update(float deltaTime, Camera *camera)override;
	void draw()override;
     Entity *clone()override{
		ID = Entity::IDcount;
		Entity::IDcount++;
		return new Mushroom(*this);}
};
