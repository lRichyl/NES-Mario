//For collisions remmember to do all your calculations with respect
//to the last state of the bounding box.
#ifndef COLLISION_H
#define COLLISION_H
#include "tile_map.h"

struct CollisionManager{
	void minkowskiDifference(SDL_Rect b1, SDL_Rect b2);
	void checkCollisions(TileMap *collisionLayer);
};

#endif
