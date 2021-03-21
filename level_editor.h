#pragma once
#include "SDL2/SDL.h"
#include "scene.h"
#include "tile.h"
#include "entity.h"
#include "camera.h"
#include "text.h"
#include "global_variables.h"
#include "tile_list.h"

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
	~TileSelectionSection(){
		SDL_DestroyTexture(selectionSquare);
		SDL_DestroyTexture(sampleSelectionSquare);
	}
};

struct LevelEditor{
	LevelEditor();
	~LevelEditor();

	Scene *level;
	std::vector<Entity*> sampleEntities;
	Entity *selectedEntity;
	TileMap *tileMapBeingEdited;
	TileMap editorLayer0;
	TileMap editorLayer1;
	TileMap editorLayer2;
	TileMap editorLayer3;
	Camera camera;

	TileSet tileSet;

	// int itemTypeCount;

	// GlyphsMap font;
	Text layerText = Text(&marioFont);
	Text entityVariantText = Text(&marioFont);

	TileSelectionSection tileSelectionSection;
	int layerBeingEdited = 0;
	// bool playScene = false;

	void udpateEditorLevel();
	void drawEditorLevel();

	void drawEditorWindow();
	void drawSampleEntities();
	void drawSelectionSquare();
	void drawSampleSelectionSquare();
	void drawTileVariant();

	void drawLayerText();
	void setLayerBeingEdited();

	void setTileMapBeingEdited();
	void setSelectedEntity();
	void setTileVariant(SDL_Event *e);
	// void setPlayMode();

	void setTileOnClick();
	void deleteTileOnClick();

	bool isMouseInSceneLimits(int xMousePos, int yMousePos);
	void initializeSampleEntities();
	void calculateSampleEntitiesPosition();
	void resizeSampleEntities();

	void loadEntitiesToScene();

	// void changeSelectionTileSize();

	//////////		READ		////////////////
	// When implementing REMEMBER to substract the xSize of the tileSelectionSection to the positions of all th entities
	// to get the real position when the actual game loads the level files.
	// bool saveLevelIntoFile();

};
