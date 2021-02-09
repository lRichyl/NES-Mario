#pragma once

struct Vector2di{
     Vector2di();
     Vector2di(int x, int y);
     int x;
     int y;

     Vector2di operator+(Vector2di v);
     Vector2di operator-(Vector2di v);

};
