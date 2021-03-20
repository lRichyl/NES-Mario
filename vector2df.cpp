#include "vector2df.h"

Vector2df::Vector2df(){
     x = 0;
     y = 0;
}

Vector2df::Vector2df(float x, float y){
     this->x = x;
     this->y = y;
}

void Vector2df::operator+(Vector2df v){
     x += v.x;
     y += v.y;
}


void Vector2df::operator-(Vector2df v){
     x -= v.x;
     y -= v.y;
}

void Vector2df::operator=(Vector2df v){
     x = v.x;
     y = v.y;
}

int Vector2df::dotProduct(Vector2df v){
     return (x * v.x) + (y * v.y);
}

// Vector2di operator-(Vector2di v){
//      Vector2di result;
//      result.x -= v.x;
//      result.y -= v.y;
//      return result;
// }
