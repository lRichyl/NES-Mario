#include "tile_list.h"
#include <iostream>

void TileSet::generateTiles(SDL_Texture *texture, int tilesetInitialX,
                    int tilesetInitialY , int tilesetWidthLimit, int tilesetHeightLimit,
                    int tileWidth, int tileHeight){

     int xNumberOfTiles = tilesetWidthLimit / tileWidth;
     int yNumberOfTiles = tilesetHeightLimit / tileHeight;

     for(int j = 0; j < yNumberOfTiles; j++){
          for(int i = 0; i < xNumberOfTiles; i++){
               SDL_Rect rect = SDL_Rect {i * tileWidth + tilesetInitialX, j * tileHeight + tilesetInitialY, tileWidth, tileHeight};
               tiles.push_back(new Tile(texture, rect, ENTITY_TYPE::GROUND));
          }
     }
     // std::cout << tiles.size() << std::endl;
}
