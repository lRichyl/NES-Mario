#pragma once
#include <vector>
#include "tile.h"
#include "SDL2/SDL.h"

struct TileList{
     std::vector<Tile> tiles;

     void generateTiles(SDL_Texture *texture, int tilesetInitialX,
                         int tilesetInitialY , int tilesetWidthLimit, int HeightLimit,
                         int tileWidth, int tileHeight);
};
