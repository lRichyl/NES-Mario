#include "sprite.h"
#include "texture.h"
#include "global_variables.h"

void Sprite::setTexture(std::string path){
	texture = loadTexture(path);
}



