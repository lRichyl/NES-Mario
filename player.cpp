#include "player.h"
#include "global_variables.h"
#include "collision.h"
#include "vector2di.h"
#include "dynamic_entities.h"
#include "question_mark.h"
#include <iostream>
#include <cmath>

Player::Player(){
	entityType = ENTITY_PLAYER;
	isStatic = false;
	isActive = true;
	// sprite.texture = loadTexture("assets/textures/mario_animations.png");
	boundingBox.w = Tile::tileSize;
	boundingBox.h = Tile::tileSize;
	// setClippingBox(98, 32, 12, 16); // This is not used when doing animated sprites
	initializeAnimationFrames();
	initializeSoundEffects();
	currentAnimation = &idleAnimation;
	timePerAnimFrameFactor = maxAnimFramesPerSecond/maxXVelocity;
}

Player::~Player(){

}
// bool updatePosition = false;
void Player::update(float deltaTime, Camera *camera){
	// localCamera = *camera;
	// std::cout << boundingBox.x << " , " << boundingBox.y << std::endl;

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

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
		if(!isAirborne){
			idleAnimation.flip = true;
			walkingAnimation.flip = true;
			jumpingAnimation.flip = true;

		}
		currentAnimation = &walkingAnimation;
		velocity.x  -= acceleration.x * deltaTime;
		if(velocity.x < -maxXVelocity){
			velocity.x = -maxXVelocity;
		}

		if(velocity.x > 0 && !isAirborne) {
			currentAnimation = &turningAnimation;
			turningAnimation.flip = true;
			if(velocity.x > velocityToPlayTurningSound){
				skidSound.play();
			}
		}else if(velocity.x < 0) skidSound.stop();

	}

	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		if(!isAirborne){
			idleAnimation.flip = false;
			walkingAnimation.flip = false;
			jumpingAnimation.flip = false;
		}

		currentAnimation = &walkingAnimation;
		velocity.x  += acceleration.x * deltaTime;
		if(velocity.x > maxXVelocity){
			velocity.x = maxXVelocity;
		}

		if(velocity.x < 0 && !isAirborne) {
			currentAnimation = &turningAnimation;
			turningAnimation.flip = false;
			if(velocity.x < -velocityToPlayTurningSound){
				skidSound.play();
			}
		}else if(velocity.x > 0) skidSound.stop();
	}

	//if the velocity is close to zero we make it zero so that the player stands still
	if( !currentKeyStates[ SDL_SCANCODE_LEFT ]&& !currentKeyStates[ SDL_SCANCODE_RIGHT ]){
		if(velocity.x > -0.8 && velocity.x < 0.8){
			velocity.x = 0;
		}
	}
	if(velocity.x == 0){
		currentAnimation = &idleAnimation;
	}



//////////////////// JUMPING////////////////////////////
	if( currentKeyStates[ SDL_SCANCODE_B ] && !wasBReleased)
	{
		if(canSetJumpingSpeed){
			jumpSound.play();
			isAirborne = true;
			if(acceleration.y < 0)
			acceleration.y += 220000* deltaTime;
			if(acceleration.y > 0) acceleration.y = 0;
			velocity.y += acceleration.y*deltaTime;
			if(velocity.y < -maxYVelocity) velocity.y = -maxYVelocity;
		}
		distanceTraveled += abs(velocity.y * deltaTime);
	}else{
		wasBReleased = true;

	}

	if(isAirborne) {
		currentAnimation = &jumpingAnimation;
		// skidSound.stop();
	}else{
		if(velocity.x > 0){
			idleAnimation.flip = false;
			walkingAnimation.flip = false;
			jumpingAnimation.flip = false;
		}else if (velocity.x < 0){
			idleAnimation.flip = true;
			walkingAnimation.flip = true;
			jumpingAnimation.flip = true;
		}

	}

	if(velocity.y > 0) isAirborne = true;
//////////////////////GRAVITY//////////////////////////////////

	if(velocity.y < 20){
		velocity.y += gravity * deltaTime;
	}



/////////////////// FRICTION/////////////////
	if(velocity.x > 0){
		velocity.x -= friction* deltaTime;
	}

	if(velocity.x < 0){
		velocity.x += friction* deltaTime;
	}
/////////////////////////////////////////////

	if(velocity.x > 0.8 || velocity.x < -0.8){

		timePerAnimFrame =  1.f / (abs(velocity.x) * timePerAnimFrameFactor);
	}


	position.x += velocity.x;
	position.y += velocity.y;


	updatePosition();
	currentAnimation->wishedTimePerFrame = timePerAnimFrame;
	// currentAnimation->update(timePerAnimFrame);
}
//
// void Player::updatePosition(){
// 	boundingBox.x = position.x - localCamera.bounds.x;
// 	boundingBox.y = position.y - localCamera.bounds.y;
// }

void Player::draw(){
	currentAnimation->animateSprite();
}

void Player::collidingWithTheFloor(Vector2df penetration){
	if(penetration.y > 0){
		wasBReleased = false;
		isAirborne = false;
		canSetJumpingSpeed = true;
		velocity.y = 0;
		acceleration.y = -60000;
		jumpSound.stop();

	}
}



void Player::collidingWithQuestionMarkBlock(Vector2df penetration, Entity *e){
	QuestionMark *questionMark = dynamic_cast<QuestionMark*>(e);

	if(penetration.y < 0 ){
		questionMark->state = questionMark->QuestionMarkState::DISABLED;
		canSetJumpingSpeed = false;
		velocity.y = 0;
	}

}

void Player::onStaticEntityCollision(Vector2df penetration, Entity *e){
	//If the player hits his head we set its velocity to 0
	if(penetration.y < 0) velocity.y = 0;
	//If we don't do this the player stands on the walls when going to the right
	if(penetration.x > 0 || penetration.x < 0) velocity.x = 0;


	if(e->entityType == ENTITY_QUESTIONMARK) collidingWithQuestionMarkBlock(penetration, e);
	collidingWithTheFloor(penetration);


	position.x = position.x - (penetration.x);
	position.y = position.y - (penetration.y);
	updatePosition();

}

void Player::onDynamicEntityCollision(Vector2df penetration, Entity *e){
	if(e->entityType == ENTITY_GOOMBA){
		Goomba *goomba = dynamic_cast<Goomba*>(e);

		if(goomba->state == goomba->GoombaState::NORMAL){
			if((penetration.x > 0 || penetration.x < 0)){
				isActive = false;
				state = PlayerState::DEAD;
				jumpSound.stop();
			}
			else if(penetration.y > 0 && velocity.y >= 0 && state == PlayerState::NORMAL){
				goomba->state = goomba->GoombaState::CRUSHED;
				velocity.y = -5;
			}
		}

	}else if(e->entityType == ENTITY_ITEM){
		e->disableAndDestroyEntity();
	}
}


void Player::initializeAnimationFrames(){
	/////IDLE ANIMATION///
	idleAnimation.texture   =  texturesContainer.marioAnimations;
	idleAnimation.bBox = &boundingBox;
	idleAnimation.frames.push_back(SDL_Rect {98, 32, 12, 16});
	/////WALKING ANIMATION///
	walkingAnimation.texture =  texturesContainer.marioAnimations;
	walkingAnimation.bBox = &boundingBox;
	walkingAnimation.frames.push_back(SDL_Rect {0, 32, 15, 16});
	walkingAnimation.frames.push_back(SDL_Rect {19, 32, 12, 16});
	walkingAnimation.frames.push_back(SDL_Rect {34, 32, 13, 16});
	///////// JUMPING ANIMATION ///////////
	jumpingAnimation.texture = texturesContainer.marioAnimations;
	jumpingAnimation.bBox = &boundingBox;
	jumpingAnimation.frames.push_back(SDL_Rect {64, 32, 16, 16});
	///////// TURNING ANIMATION /////////////
	turningAnimation.texture = texturesContainer.marioAnimations;
	turningAnimation.bBox = &boundingBox;
	turningAnimation.frames.push_back(SDL_Rect {50, 32, 13, 16});
}

void Player::initializeSoundEffects(){
	jumpSound.channel = 1;
	jumpSound.sound = soundsContainer.marioJump;
	skidSound.channel = 2;
	skidSound.sound = soundsContainer.skid;
}
