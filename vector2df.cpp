#include "vector2df.h"

Vector2df::Vector2df(){
     x = 0;
     y = 0;
}

Vector2df::Vector2df(float x, float y){
     this->x = x;
     this->y = y;
}

Vector2df operator+(Vector2df v){
     Vector2df result;
     result.x += v.x;
     result.y += v.y;
     return result;
}

Vector2df operator-(Vector2df v){
     Vector2df result;
     result.x -= v.x;
     result.y -= v.y;
     return result;
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
