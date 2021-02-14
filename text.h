#pragma once
#include <string>
#include <map>
#include <vector>
#include "vector2di.h"
#include "SDL2/SDL.h"



struct Text{
     Text();
     std::string currentText;
     std::map<std::string, SDL_Rect> stringToGlyphMap{};
     std::vector<SDL_Rect> glyphsToRender {};
     std::vector<SDL_Rect> glyphsPositions {};
     SDL_Texture *texture = nullptr;
     int x;
     int y;
     int size;

     void renderText(std::string text);
     void setGlyphs();
     void initializeMapofGlyphs();

     ~Text(){
          SDL_DestroyTexture(texture);
     }


};
