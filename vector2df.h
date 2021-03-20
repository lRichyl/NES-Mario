#pragma once

struct Vector2df{
     Vector2df();
     Vector2df(float x, float y);
     float x;
     float y;

     void operator+(Vector2df v);
     void operator-(Vector2df v);
     void operator=(Vector2df v);

     int dotProduct(Vector2df);

};
