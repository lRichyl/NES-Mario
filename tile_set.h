#pragma once
#include <vector>
#include "tile.h"
#include "SDL2/SDL.h"

struct TileSet{
     std::vector<Tile*> tiles;
     // SDL_Texture *t = loadTexture("assets/textures/mario_blocks.png");

     void generateTiles(SDL_Texture *texture, int tilesetInitialX,
                         int tilesetInitialY , int tilesetWidthLimit, int HeightLimit,
                         int tileWidth, int tileHeight);
};
