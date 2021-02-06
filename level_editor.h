#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H
#include "SDL2/SDL.h"
#include "scene.h"
#include "tile.h"

struct TileSelectionSection{
	TileSelectionSection();
	SDL_Rect screenSection;
	SDL_Rect border;
	SDL_Texture *selectionSquare;
	SDL_Texture *sampleSelectionSquare;
	SDL_Rect selectionSquareBox;
	SDL_Rect sampleSelectionSquareBox;
	int xSize = 120;
	int offset = 12;
	int tilesPerRow = 3;
	int editorTileSize = 32;
	
	void draw();
};

struct LevelEditor{
	LevelEditor();
	~LevelEditor();
	
	Scene level;
	std::vector<Entity*> sampleEntities;
	Entity *selectedEntity;
	TileMap *tileMapBeingEdited;
	TileSelectionSection tileSelectionSection;
	int layerBeingEdited = 0;
	
	void drawEditorWindow();
	void drawSampleEntities();
	void drawSelectionSquare();
	void drawSampleSelectionSquare();
	void setTileMapBeingEdited();
	void setTileOnClick();
	void setSelectedEntity();
	void deleteTileOnClick();
	bool isMouseInSceneLimits(int xMousePos, int yMousePos);
	void initializeSampleEntities();
	void calculateSampleEntitiesPosition();
	void resizeSampleEntities();
	
	// void changeSelectionTileSize();
	
	//////////		READ		////////////////
	// When implementing REMEMBER to substract the xSize of the tileSelectionSection to the positions of all th entities
	// to get the real position when the actual game loads the level files.
	// bool saveLevelIntoFile(); 
	
};

#endif