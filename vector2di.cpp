#include "vector2di.h"

Vector2di::Vector2di(){
     x = 0;
     y = 0;
}

Vector2di::Vector2di(int x, int y){
     this->x = x;
     this->y = y;
}

Vector2di operator+(Vector2di v){
     Vector2di result;
     result.x += v.x;
     result.y += v.y;
     return result;
}

Vector2di operator-(Vector2di v){
     Vector2di result;
     result.x -= v.x;
     result.y -= v.y;
     return result;
}
