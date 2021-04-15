#pragma once
#include "sprite.h"
#include "tile_map.h"
#include "entity.h"
#include "SDL2/SDL.h"
#include "sound_effects.h"

struct QuestionMark : public Entity{

	enum QuestionMarkState{
		NORMAL,
		DISABLED
	};

	QuestionMark();

	float maxYmovement = position.y;
	float originalPosition;
	bool pushBlock = true;
	bool spawnItem = true;
	float speed = 5;

	Sprite blockUnused;
     Sprite blockUsed;
	// Sprite *currentAnimation = nullptr;

	SoundEffect bumpingSound;

	TileMap *tilemapToSpawnItemsOn;
	ITEM_TYPE itemType = ITEM_MUSHROOM;
	QuestionMarkState state = QuestionMarkState::NORMAL;

     void initAnimation();
	void initSounds();
	void initParameters();
	void update(float deltaTime, Camera *camera) override;
     void draw()override;

	Entity *clone()override{
		Entity::IDcount++;
		ID = Entity::IDcount;
		QuestionMark *q = new QuestionMark(*this);
		// std::cout << position.y << " , "  << q->position.y << std::endl;
		// q->position.y = position.y;
		return q;}
};
