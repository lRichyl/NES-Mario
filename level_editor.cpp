#include "level_editor.h"
#include "player.h"
#include "dynamic_entities.h"
#include "global_variables.h"
#include "renderer.h"
#include <iostream>
#include "question_mark.h"
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
	camera.resetCamera();
	initializeSampleEntities();
	selectedEntity = sampleEntities[0];
	calculateSampleEntitiesPosition();
	layerBeingEdited = 0;
	layerText.size = 16;
	layerText.x = WINDOW_WIDTH - layerText.size;
	layerText.y = 0;
}

void TileSelectionSection::draw(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &screenSection);

	SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
	SDL_RenderFillRect(renderer, &border);
}

// void LevelEditor::resizeSampleEntities(){
	// for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		// if(sampleEntities[i] != nullptr){
			// sampleEntities[i]->setTileSize(tileSelectionSection.editorTileSize);
		// }
	// }
// }

void LevelEditor::initializeSampleEntities(){
	sampleEntities.push_back(new PlayerTile());
	sampleEntities.push_back(new GoombaTile());
	sampleEntities.push_back(new Ground());
	sampleEntities.push_back(new SolidBlock());
	sampleEntities.push_back(new Brick());
	sampleEntities.push_back(new QuestionMarkTile());
	sampleEntities.push_back(new CloudLeftTop());
	sampleEntities.push_back(new CloudRightTop());
	sampleEntities.push_back(new CloudLeftDown());
	sampleEntities.push_back(new CloudRightDown());
	sampleEntities.push_back(new PipeLeftTop());
	sampleEntities.push_back(new PipeRightTop());
	sampleEntities.push_back(new PipeLeftDown());
	sampleEntities.push_back(new PipeRightDown());
	sampleEntities.push_back(new MountTopLeft());
	sampleEntities.push_back(new MountTopRight());
	sampleEntities.push_back(new MountDownLeft());
	sampleEntities.push_back(new MountDownRight());
	sampleEntities.push_back(new MountTop());
	sampleEntities.push_back(new MountDown());

	// resizeSampleEntities();
}

void LevelEditor::calculateSampleEntitiesPosition(){
	int row = 0;
	int col = 0;
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){
			Entity *e = sampleEntities[i];
			e->boundingBox.x = (col * tileSelectionSection.editorTileSize) + tileSelectionSection.offset + 1;
			e->boundingBox.y = (row * tileSelectionSection.editorTileSize) + tileSelectionSection.offset + 1;
			// e->draw();
			col++;
			if(col == (tileSelectionSection.tilesPerRow)){
				col = 0;
				row++;
			}
		}
	}
}

void LevelEditor::setTileMapBeingEdited(){
	switch(layerBeingEdited){
		case 0: tileMapBeingEdited = &editorLayer0;
		break;
		case 1: tileMapBeingEdited = &editorLayer1;
		break;
		case 2: tileMapBeingEdited = &editorLayer2;
		break;
		case 3: tileMapBeingEdited = &editorLayer3;
		break;
		default:
		tileMapBeingEdited = &editorLayer0;
		break;
	}
}

void LevelEditor::setLayerBeingEdited(){
	if(layerBeingEdited > 3) layerBeingEdited = 0;
	else if(layerBeingEdited < 0 )layerBeingEdited = 3;
	setTileMapBeingEdited();
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
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.bounds.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.bounds.y);

		if(xTile >= 0 && yTile >= 0){
			selectedEntity->xTile = xTile;
			selectedEntity->yTile = yTile;
			selectedEntity->position.x = xTile * tileMapBeingEdited->tileWidth;
			selectedEntity->position.y = yTile * tileMapBeingEdited->tileHeight;


			if(tileMapBeingEdited->entities[xTile][yTile] == nullptr){
				Entity *newEntity = selectedEntity->clone();
				// std::cout << newEntity->position.y << " , " << selectedEntity->position.y << std::endl;
				tileMapBeingEdited->addEntityOnTile(xTile, yTile, newEntity);
			}
		}
	}
}

void LevelEditor::deleteTileOnClick(){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) && isMouseInSceneLimits(mouseX, mouseY)){
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.bounds.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.bounds.y);

		delete tileMapBeingEdited->entities[xTile][yTile];
		tileMapBeingEdited->entities[xTile][yTile] = nullptr;
	}
}

void LevelEditor::setSelectedEntity(){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && (mouseX > tileSelectionSection.offset && mouseX < tileSelectionSection.xSize - tileSelectionSection.offset)){
		int xTile = (mouseX - tileSelectionSection.offset)  / tileSelectionSection.editorTileSize;
		int yTile = (mouseY - tileSelectionSection.offset) / tileSelectionSection.editorTileSize;


		unsigned int entityInMouseID = xTile + (yTile * tileSelectionSection.tilesPerRow);

		if(entityInMouseID < sampleEntities.size()){
			selectedEntity = sampleEntities[entityInMouseID];
		}

	}
}

void LevelEditor::udpateEditorLevel(){
	camera.updatePosition();
	editorLayer0.update(deltaTfixed, &camera.bounds);
	editorLayer1.update(deltaTfixed, &camera.bounds);
	editorLayer2.update(deltaTfixed, &camera.bounds);
	editorLayer3.update(deltaTfixed, &camera.bounds);
}

void LevelEditor::drawEditorLevel(){
	editorLayer0.draw();
	editorLayer1.draw();
	editorLayer2.draw();
	editorLayer3.draw();
}

void LevelEditor::drawSampleEntities(){
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){
			sampleEntities[i]->boundingBox.w = tileSelectionSection.editorTileSize;
			sampleEntities[i]->boundingBox.h = tileSelectionSection.editorTileSize;
			sampleEntities[i]->draw();

			sampleEntities[i]->boundingBox.w = Tile::tileSize;
			sampleEntities[i]->boundingBox.h = Tile::tileSize;
		}
	}
}

void LevelEditor::drawSelectionSquare(){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((isMouseInSceneLimits(mouseX, mouseY))){
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.bounds.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.bounds.y);
		tileSelectionSection.selectionSquareBox.x = (xTile * tileMapBeingEdited->tileWidth) - camera.bounds.x;
		tileSelectionSection.selectionSquareBox.y = (yTile * tileMapBeingEdited->tileHeight) - camera.bounds.y;

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

		SDL_RenderCopy(renderer, tileSelectionSection.sampleSelectionSquare, nullptr, &tileSelectionSection.sampleSelectionSquareBox);
	}
}


void LevelEditor::drawEditorWindow(){
	drawSelectionSquare();
	tileSelectionSection.draw();
	drawSampleEntities();
	drawSampleSelectionSquare();
}

void LevelEditor::drawLayerText(){
	layerText.renderText(std::to_string(layerBeingEdited));
}

static void setDynamicEntityPosition(Entity* tileEntity, Entity* d){
	d->position.x = tileEntity->position.x - CAMERA.bounds.x;
	d->position.y = tileEntity->position.y - CAMERA.bounds.y;
}

void LevelEditor::loadEntitiesToScene(){
	for(unsigned int i = 0; i < editorLayer0.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer0.entities[i].size(); j++){
			if(editorLayer0.entities[i][j] != nullptr){
				level->layer0.entities[i][j] = editorLayer0.entities[i][j]->clone();

			}
		}
	}

	for(unsigned int i = 0; i < editorLayer1.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer1.entities[i].size(); j++){
			if(editorLayer1.entities[i][j] != nullptr){
				level->layer1.entities[i][j] = editorLayer1.entities[i][j]->clone();

			}
		}
	}

	for(unsigned int i = 0; i < editorLayer2.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer2.entities[i].size(); j++){
			Entity *e = editorLayer2.entities[i][j];
			if(e != nullptr){
				if(e->isStatic ){
						level->layer2.entities[i][j] = e->clone();


					// std::cout << level->layer2.entities[i][j]->position.y << " , " << e->position.y << std::endl;

				}else
				if(e->entityType == ENTITY_TYPE::PLAYER){
					Player *p = new Player();
					setDynamicEntityPosition(e, p);

					level->layer2.dynamicEntities.push_back(p);

				} else if(e->entityType == ENTITY_TYPE::GOOMBA){
					Goomba *g = new Goomba();
					setDynamicEntityPosition(e, g);

					level->layer2.dynamicEntities.push_back(g);

				}else if(e->entityType == ENTITY_TYPE::QUESTIONMARK){
					QuestionMark *q = new QuestionMark();
					setDynamicEntityPosition(e, q);
					q->initParameters();
					q->tilemapToSpawnItemsOn = &level->layer2;
					level->layer2.dynamicEntities.push_back(q);
				}
			}
		}
	}


	for(unsigned int i = 0; i < editorLayer3.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer3.entities[i].size(); j++){
			if(editorLayer3.entities[i][j] != nullptr){
					level->layer3.entities[i][j] = editorLayer3.entities[i][j]->clone();
			}
		}
	}
}


LevelEditor::~LevelEditor(){
	for(unsigned int i = 0; i < sampleEntities.size() ; i++){
		if(sampleEntities[i] != nullptr){
			delete sampleEntities[i];
		}
	}
}
