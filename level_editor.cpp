#include "level_editor.h"
#include "player.h"
#include "global_variables.h"
#include "renderer.h"
#include <iostream>
using namespace std;

TileSelectionSection::TileSelectionSection(){
	screenSection.w = xSize;
	screenSection.h = rendererInfo.height;
	screenSection.x = 0;
	screenSection.y = 0;
	border.w = 8;
	border.h = rendererInfo.height;
	border.x = xSize;
	border.y = 0;
	editorTileSize = 32;
	selectionSquare = loadTexture("assets/textures/selection_square.png");
	sampleSelectionSquare = loadTexture("assets/textures/selected_entity_selection.png");
	selectionSquareBox.w = Tile::tileSize;
	selectionSquareBox.h = Tile::tileSize;
	sampleSelectionSquareBox.w = editorTileSize;
	sampleSelectionSquareBox.h = editorTileSize;
}

LevelEditor::LevelEditor(){
	initializeSampleEntities();
	calculateSampleEntitiesPosition();
}

void TileSelectionSection::draw(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderFillRect(renderer, &screenSection);
	
	SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255); 
	SDL_RenderFillRect(renderer, &border);
}

void LevelEditor::resizeSampleEntities(){
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){				
			sampleEntities[i]->setTileSize(tileSelectionSection.editorTileSize);			
		}	
	}
}

void LevelEditor::initializeSampleEntities(){
	sampleEntities.push_back(new Ground());
	sampleEntities.push_back(new Brick());
	sampleEntities.push_back(new QuestionMark());
	sampleEntities.push_back(new CloudLeftTop());
	sampleEntities.push_back(new CloudRightTop());
	sampleEntities.push_back(new CloudLeftDown());
	sampleEntities.push_back(new CloudRightDown());
	sampleEntities.push_back(new PipeLeftTop());
	sampleEntities.push_back(new PipeRightTop());
	sampleEntities.push_back(new PipeLeftDown());
	sampleEntities.push_back(new PipeRightDown());	
	
	resizeSampleEntities();
}

void LevelEditor::calculateSampleEntitiesPosition(){
	int row = 0;
	int col = 0;
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){
			Entity *e = sampleEntities[i];			
			e->sprite.boundingBox.x = (col * tileSelectionSection.editorTileSize) + tileSelectionSection.offset + 1;
			e->sprite.boundingBox.y = (row * tileSelectionSection.editorTileSize) + tileSelectionSection.offset + 1;
			// e->draw();
			col++;
			if(col == (tileSelectionSection.xSize - tileSelectionSection.offset)/tileSelectionSection.editorTileSize) {
				col = 0;
				row++;
			}
		}
	}	
}

void LevelEditor::setTileMapBeingEdited(){
	switch(layerBeingEdited){
		case 0: tileMapBeingEdited = &level.layer0;
		break;
		case 1: tileMapBeingEdited = &level.layer1;
		break;
		case 2: tileMapBeingEdited = &level.layer2;
		break;
		case 3: tileMapBeingEdited = &level.layer3;
		break;
	}
}

bool LevelEditor::isMouseInSceneLimits(int xMousePos, int yMousePos){
	if(xMousePos > tileSelectionSection.xSize)
		return true;
	return false;
}

void LevelEditor::setTileOnClick(){
	int mouseX;
	int mouseY;	
	SDL_GetMouseState(&mouseX, &mouseY);	
	if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && isMouseInSceneLimits(mouseX, mouseY)){
		int xTile = tileMapBeingEdited->getXTile(mouseX + level.camera->x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + level.camera->y);
		
		selectedEntity->x = xTile * tileMapBeingEdited->tileWidth;
		selectedEntity->y = yTile * tileMapBeingEdited->tileHeight;
		
		// std::cout << xTile << ", " << yTile << std::endl;

		Entity *newEntity = selectedEntity->clone();
		// }
		tileMapBeingEdited->addEntityOnTile(xTile, yTile, newEntity);		
	}
}

void LevelEditor::deleteTileOnClick(){
	int mouseX;
	int mouseY;	
	SDL_GetMouseState(&mouseX, &mouseY);	
	if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) && isMouseInSceneLimits(mouseX, mouseY)){
		int xTile = tileMapBeingEdited->getXTile(mouseX + level.camera->x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + level.camera->y);
		
		tileMapBeingEdited->entities[xTile][yTile] = nullptr; 		
	}
}

void LevelEditor::drawSampleEntities(){
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){
			sampleEntities[i]->draw();
			
		}
	}
}

void LevelEditor::drawSelectionSquare(){
	int mouseX;
	int mouseY;	
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((isMouseInSceneLimits(mouseX, mouseY))){
		int xTile = tileMapBeingEdited->getXTile(mouseX + level.camera->x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + level.camera->y);
		tileSelectionSection.selectionSquareBox.x = (xTile * tileMapBeingEdited->tileWidth) - level.camera->x;
		tileSelectionSection.selectionSquareBox.y = (yTile * tileMapBeingEdited->tileHeight) - level.camera->y;
		// sprite.boundingBox.x = x - camera->x;
		// sprite.boundingBox.y = y - camera->y;

		SDL_RenderCopy(renderer, tileSelectionSection.selectionSquare, nullptr, &tileSelectionSection.selectionSquareBox);
	}
}

void LevelEditor::drawSampleSelectionSquare(){
	int mouseX;
	int mouseY;	
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > tileSelectionSection.offset && mouseX < tileSelectionSection.xSize - tileSelectionSection.offset){
		int xTile = (mouseX - tileSelectionSection.offset) / tileSelectionSection.editorTileSize;
		int yTile = (mouseY - tileSelectionSection.offset) / tileSelectionSection.editorTileSize;
		tileSelectionSection.sampleSelectionSquareBox.x = tileSelectionSection.offset + (xTile * tileSelectionSection.editorTileSize);
		tileSelectionSection.sampleSelectionSquareBox.y = tileSelectionSection.offset + (yTile * tileSelectionSection.editorTileSize);
		// sprite.boundingBox.x = x - camera->x;
		// sprite.boundingBox.y = y - camera->y;
		// COMENTARIO DE PRUEBA
		SDL_RenderCopy(renderer, tileSelectionSection.sampleSelectionSquare, nullptr, &tileSelectionSection.sampleSelectionSquareBox);
	}
}
	

void LevelEditor::drawEditorWindow(){
	drawSelectionSquare();
	tileSelectionSection.draw();
	drawSampleEntities();
	drawSampleSelectionSquare();
}

// void LevelEditor::changeSelectionTileSize(){
	// for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		// if(sampleEntities[i] != nullptr){				
			// sampleEntities[i]->setClippingBox(0, 0, tileSelectionSection.editorTileSize, tileSelectionSection.editorTileSize);
		// }	
	// }
// }

LevelEditor::~LevelEditor(){
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){				
			delete sampleEntities[i];
		}	
	}
}