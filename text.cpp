#include <iostream>
#include "text.h"
#include "texture.h"
#include "global_variables.h"

GlyphsMap::GlyphsMap(){
     // initializeMapofGlyphs();
}

Text::Text(GlyphsMap *glyphsMap){
     this->glyphsMap = glyphsMap;
}

void Text::renderText(std::string text){
     if(currentText != text){
          currentText = text;
          glyphsToRender.clear();
          glyphsPositions.clear();
          setGlyphs();
     }
     for(unsigned int i = 0;i < glyphsToRender.size(); i++){
          SDL_RenderCopy(renderer, glyphsMap->texture, &glyphsToRender[i], &glyphsPositions[i]);
     }
}
void Text::setGlyphs(){
     for(unsigned int i = 0; i < currentText.size();i++ ){
          std::string t = currentText.substr(i,1);
          glyphsToRender.push_back(glyphsMap->stringToGlyphMap[t]);
          int xFinalPos = (i * size) + x;
          int yFinalPos = y;
          glyphsPositions.push_back(SDL_Rect {xFinalPos, yFinalPos, size, size});
     }
}
void GlyphsMap::initializeMapofGlyphs(){
     texture = loadTexture("assets/textures/nesfont_white.png");
     
     stringToGlyphMap.insert(
     {{"A", SDL_Rect {15, 31, 16, 16}},
      {"B", SDL_Rect {31, 31, 16, 16}},
      {"C", SDL_Rect {47, 31, 16, 16}},
      {"D", SDL_Rect {63, 31, 16, 16}},
      {"E", SDL_Rect {79, 31, 16, 16}},
      {"F", SDL_Rect {95, 31, 16, 16}},
      {"G", SDL_Rect {111, 31, 16, 16}},
      {"H", SDL_Rect {127, 31, 16, 16}},
      {"I", SDL_Rect {143, 31, 16, 16}},
      {"J", SDL_Rect {159, 31, 16, 16}},
      {"K", SDL_Rect {175, 31, 16, 16}},
      {"L", SDL_Rect {191, 31, 16, 16}},
      {"M", SDL_Rect {207, 31, 16, 16}},
      {"N", SDL_Rect {223, 31, 16, 16}},
      {"O", SDL_Rect {239, 31, 16, 16}},
      {"P", SDL_Rect {0, 47, 16, 16}},
      {"Q", SDL_Rect {15, 47, 16, 16}},
      {"R", SDL_Rect {31, 47, 16, 16}},
      {"S", SDL_Rect {47, 47, 16, 16}},
      {"T", SDL_Rect {65, 47, 14, 16}},
      {"U", SDL_Rect {79, 47, 16, 16}},
      {"V", SDL_Rect {95, 47, 16, 16}},
      {"W", SDL_Rect {111, 47, 16, 16}},
      {"X", SDL_Rect {127, 47, 16, 16}},
      {"Y", SDL_Rect {145, 47, 16, 16}},
      {"Z", SDL_Rect {159, 47, 16, 16}},
      {"0", SDL_Rect { 0, 15, 16, 16}},
      {"1", SDL_Rect { 17, 15, 14, 16}},
      {"2", SDL_Rect { 31, 15, 16, 16}},
      {"3", SDL_Rect { 47, 15, 16, 16}},
      {"4", SDL_Rect { 63, 15, 16, 16}},
      {"5", SDL_Rect { 79, 15, 16, 16}},
      {"6", SDL_Rect { 95, 15, 16, 16}},
      {"7", SDL_Rect { 111, 15, 16, 16}},
      {"8", SDL_Rect { 127, 15, 16, 16}},
      {"9", SDL_Rect { 143, 15, 16, 16}},
      {".", SDL_Rect { 223, 0, 16, 16}}
     });
}
