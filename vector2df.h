#pragma once

struct Vector2df{
     Vector2df();
     Vector2df(float x, float y);
     float x;
     float y;

     Vector2df operator+(Vector2df v);
     Vector2df operator-(Vector2df v);

     int dotProduct(Vector2df);

};
