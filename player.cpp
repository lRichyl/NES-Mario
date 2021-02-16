#include "player.h"
#include "global_variables.h"
#include "collision.h"
#include "vector2di.h"
#include <iostream>
#include <cmath>

Player::Player(){
	entityType = ENTITY_TYPE::PLAYER;
	isStatic = false;
	isActive = true;
	// sprite.texture = loadTexture("assets/textures/mario_animations.png");
	boundingBox.w = Tile::tileSize;
	boundingBox.h = Tile::tileSize;
	setClippingBox(98, 32, 12, 16); // This is not used when doing animated sprites
	initializeAnimationFrames();
	currentAnimation = &idleAnimation;
}

Player::~Player(){
	//Remember to always destroy the textures or it can cause a memory leak.
	//This will be done in the future in a texture manager.
	SDL_DestroyTexture(idleAnimation.texture);
	SDL_DestroyTexture(walkingAnimation.texture);
}
// bool updatePosition = false;
void Player::update(float deltaTime, SDL_Rect *camera){
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	// if(updatePosition){
	// 	sprite.boundingBox.x = position.x - camera->x;
	// 	sprite.boundingBox.y = position.y - camera->y;
	// }

	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{
		// position.y -= velocity.y * ydirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{
		// position.y += velocity.y * ydirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		currentAnimation = &walkingAnimation;
		velocity.x  -= acceleration.x * deltaTime;
		if(velocity.x < -maxVelocity){
			velocity.x = -maxVelocity;
		}
		// acceleration.x += 3 * deltaTime;
		// position.x -= velocity.x * xdirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		currentAnimation = &walkingAnimation;
		velocity.x  += acceleration.x * deltaTime;
		if(velocity.x > maxVelocity){
			velocity.x = maxVelocity;
		}
		// acceleration.x += 3 * deltaTime;
		// position.x += velocity.x * xdirection * deltaTime;
	}
	if(canJump){
		if( currentKeyStates[ SDL_SCANCODE_B ] )
		{
			acceleration.y -= .8;
			if(acceleration.y > -8) acceleration.y = -8;
			// if(acceleration.y < -80 )deaccel -= .1;
			velocity.y += acceleration.y * deltaTime;
			distanceTraveled += velocity.y * deltaTime;
			if(velocity.y <= -2) velocity.y = -2;
			if(distanceTraveled < -250 * deltaTime)
				canJump = false;

			// if(velocity.y < -maxVelocity){
				// 	velocity.y = -maxVelocity;
				// }


		}
		// if(velocity.y < -5){
		// 	// velocity.y = 0;
		// 	// acceleration.y = 0;
		// 	isFalling = true;
		// 	canJump = false;
		// }else{
		// 	velocity.y += acceleration.y * deltaTime;
		// }
	}else{
		acceleration.y = 0;
		distanceTraveled = 0;
		// deaccel = 2.5;
	}
	velocity.y += gravity * deltaTime;





	if(velocity.x > 0){
		velocity.x -= 30* deltaTime;
		// if(velocity.x < 0.03 && velocity.x > 0 ) velocity.x = 0;
	}

	if(velocity.x < 0){
		velocity.x += 30* deltaTime;
		// if(velocity.x > -0.03 && velocity.x < 0) velocity.x = 0;
	}

	if((int)velocity.x == 0){
		currentAnimation =  &idleAnimation;
	}

	std::cout << distanceTraveled << std::endl;
	// if(acceleration.x > 3) acceleration.x =3;

	// acceleration.x -= 1;
	position.x += (int)velocity.x;
	position.y += velocity.y;
	xdirection = 1;
	ydirection = 1;

	updatePosition();
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	// if(currentAnimation->texture == nullptr){ std::cout << "NULL" << std::endl;}
	// std::cout << currentAnimation->boundingBox.x << " , " << currentAnimation->boundingBox.x << std::endl;
}

void Player::updatePosition(){
	boundingBox.x = position.x - CAMERA.bounds.x;
	boundingBox.y = position.y - CAMERA.bounds.y;
	// std::cout << boundingBox.x << " , " << boundingBox.x << std::endl;

}

void Player::draw(){
	// SDL_RenderCopy( renderer, sprite.texture, &clippingBox, &sprite.boundingBox );
	currentAnimation->animateSprite(0.08);
}


void Player::onCollision(Vector2df penetration){
		// std::cout << penetrationVector.x << " , " << penetrationVector.y << std::endl;
		// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;
	if(penetration.y > 0 && canJump == false){
		canJump = true;
		isFalling = false;
		velocity.y = 0;
	}
	if(penetration.y > 0){
		velocity.y = 0;
	}

	position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}

void Player::initializeAnimationFrames(){
	/////IDLE ANIMATION///
	idleAnimation.texture    =  loadTexture("assets/textures/mario_animations.png");
	idleAnimation.bBox = &boundingBox;
	idleAnimation.frames.push_back(SDL_Rect {98, 32, 12, 16});
	/////WALKING ANIMATION///
	walkingAnimation.texture =  loadTexture("assets/textures/mario_animations.png");
	walkingAnimation.bBox = &boundingBox;
	walkingAnimation.frames.push_back(SDL_Rect {0, 32, 15, 16});
	walkingAnimation.frames.push_back(SDL_Rect {34, 32, 13, 16});
	walkingAnimation.frames.push_back(SDL_Rect {19, 32, 12, 16});
}
