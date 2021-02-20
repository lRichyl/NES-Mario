#pragma once
#include <string>
#include <map>
#include <vector>
#include "vector2di.h"
#include "SDL2/SDL.h"


struct GlyphsMap{
     GlyphsMap();
     std::map<std::string, SDL_Rect> stringToGlyphMap{};
     SDL_Texture *texture = nullptr;

     void initializeMapofGlyphs();
     ~GlyphsMap(){
          SDL_DestroyTexture(texture);
     }
};

struct Text{
     Text(GlyphsMap *glyphsMap);
     std::string currentText;
     GlyphsMap *glyphsMap;
     std::vector<SDL_Rect> glyphsToRender {};
     std::vector<SDL_Rect> glyphsPositions {};

     int x;
     int y;
     int size;

     void renderText(std::string text);

     void setGlyphs();

};
