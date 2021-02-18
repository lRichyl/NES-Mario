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
		idleAnimation.flip = true;
		currentAnimation = &walkingAnimation;
		walkingAnimation.flip = true;
		velocity.x  -= acceleration.x * deltaTime;
		if(velocity.x < -maxXVelocity){
			velocity.x = -maxXVelocity;
		}
		// acceleration.x += 3 * deltaTime;
		// position.x -= velocity.x * xdirection * deltaTime;
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		idleAnimation.flip = false;
		currentAnimation = &walkingAnimation;
		walkingAnimation.flip = false;
		velocity.x  += acceleration.x * deltaTime;
		if(velocity.x > maxXVelocity){
			velocity.x = maxXVelocity;
		}
		// acceleration.x += 3 * deltaTime;
		// position.x += velocity.x * xdirection * deltaTime;
	}

	//if the velocity is close to zero we make it zero so that the player stands still
	if( !currentKeyStates[ SDL_SCANCODE_LEFT ]&& !currentKeyStates[ SDL_SCANCODE_RIGHT ]){
		currentAnimation = &idleAnimation;
		if(velocity.x > -0.2 && velocity.x < 0.2){
			velocity.x = 0;
		}
	}

//////////////////// JUMPING////////////////////////////
	if( currentKeyStates[ SDL_SCANCODE_B ] && !wasBReleased)
	{

		if(canJump){
			if(canSetJumpingSpeed){
				velocity.y += acceleration.y*deltaTime;
				if(acceleration.y < 0)
					acceleration.y += 450 * deltaTime;
				if(velocity.y < -maxYVelocity) velocity.y = -maxYVelocity;
				// velocity.y = -3 ;
				// canSetJumpingSpeed = false;
				// canJump = false;
			}
		}else{
			distanceTraveled = 0;

		}


		// velocity.y += 10 * deltaTime;
		distanceTraveled += abs(velocity.y * deltaTime);
	}else{
		wasBReleased = true;
		// std::cout << "b release" << std::endl;

	}

////////////////////////////////////////////////////////
	velocity.y += gravity * deltaTime;




/////////////////// FRICTION/////////////////
	if(velocity.x > 0){
		velocity.x -= friction* deltaTime;
		// if(velocity.x < 0.03 && velocity.x > 0 ) velocity.x = 0;
	}

	if(velocity.x < 0){
		velocity.x += friction* deltaTime;
		// if(velocity.x > -0.03 && velocity.x < 0) velocity.x = 0;
	}
/////////////////////////////////////////////


	std::cout << walkingAnimation.frameIndex << std::endl;
	position.x += velocity.x;
	position.y += velocity.y;

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
		velocity.y = 0;
	}

	if(penetration.y > 0){
		acceleration.y = -100;
		wasBReleased = false;
		canJump = true;
		canSetJumpingSpeed = true;
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
