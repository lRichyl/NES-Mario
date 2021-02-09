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
	camera.x = 0;
	camera.y = 0;
	camera.w = 1280;
	camera.h = 720;
	initializeSampleEntities();
	selectedEntity = sampleEntities[0];
	calculateSampleEntitiesPosition();
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

	// resizeSampleEntities();
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
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.y);

		selectedEntity->xTile = xTile;
		selectedEntity->yTile = yTile;
		selectedEntity->position.x = xTile * tileMapBeingEdited->tileWidth;
		selectedEntity->position.y = yTile * tileMapBeingEdited->tileHeight;
		// }

		if(tileMapBeingEdited->entities[xTile][yTile] == nullptr){
			Entity *newEntity = selectedEntity->clone();
			// if(!selectedEntity->isStatic){
				// newEntity->sprite.boundingBox.x = selectedEntity->x;
				// newEntity->sprite.boundingBox.y = selectedEntity->y;// selectedEntity->ystd::cout << xTile << ", " << yTile << std::endl;
			// }
			// int count = 0;
		// for(unsigned int i = 0; i < tileMapBeingEdited.entities.size() ; i++){
			// for(unsigned int j = 0; j < tileMapBeingEdited.entities[i].size(); j++){
				// if(tileMapBeingEdited.entities[i][j] != nullptr){
					// count++;
				// }
			// }
		// }
			// std::cout << count << std::endl;
			tileMapBeingEdited->addEntityOnTile(xTile, yTile, newEntity);
		}
	}
}

void LevelEditor::deleteTileOnClick(){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) && isMouseInSceneLimits(mouseX, mouseY)){
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.y);

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


		int entityInMouseID = xTile + (yTile * tileSelectionSection.tilesPerRow);

		selectedEntity = sampleEntities[entityInMouseID];

	}
}
float x = 0;
float y = 0;

void LevelEditor::udpateEditorLevel(){
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if( currentKeyStates[ SDL_SCANCODE_W ] )
	{
		y -= 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_S ] )
	{
		y += 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_A ] )
	{
		x -= 60 * deltaT;
	}
	if( currentKeyStates[ SDL_SCANCODE_D ] )
	{
		x += 60 * deltaT;
	}
	camera.x = x;
	camera.y = y;
	if(camera.x < 0) {
		camera.x = 0;
	}
	if(camera.y < 0) {
		camera.y = 0;
	}
	editorLayer0.update(deltaT, &camera);
	editorLayer1.update(deltaT, &camera);
	editorLayer2.update(deltaT, &camera);
	editorLayer3.update(deltaT, &camera);
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
			sampleEntities[i]->sprite.boundingBox.w = tileSelectionSection.editorTileSize;
			sampleEntities[i]->sprite.boundingBox.h = tileSelectionSection.editorTileSize;
			sampleEntities[i]->draw();

			sampleEntities[i]->sprite.boundingBox.w = Tile::tileSize;
			sampleEntities[i]->sprite.boundingBox.h = Tile::tileSize;
		}
	}
}

void LevelEditor::drawSelectionSquare(){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if ((isMouseInSceneLimits(mouseX, mouseY))){
		int xTile = tileMapBeingEdited->getXTile(mouseX + camera.x);
		int yTile = tileMapBeingEdited->getYTile(mouseY + camera.y);
		tileSelectionSection.selectionSquareBox.x = (xTile * tileMapBeingEdited->tileWidth) - camera.x;
		tileSelectionSection.selectionSquareBox.y = (yTile * tileMapBeingEdited->tileHeight) - camera.y;
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

static void setDynamicEntityPosition(Entity* tileEntity, Entity* d){
	d->position.x = tileEntity->position.x;
	d->position.y = tileEntity->position.y;
	// d->x = tileEntity->sprite.boundingBox.x;
	// d->y = tileEntity->sprite.boundingBox.y;
}

void LevelEditor::loadEntitiesToScene(){
	for(unsigned int i = 0; i < editorLayer0.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer0.entities[i].size(); j++){
			if(editorLayer0.entities[i][j] != nullptr){
				if(editorLayer0.entities[i][j]->isStatic){
					level->layer0.entities[i][j] = editorLayer0.entities[i][j]->clone();
				}
			}
		}
	}

	for(unsigned int i = 0; i < editorLayer1.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer1.entities[i].size(); j++){
			if(editorLayer1.entities[i][j] != nullptr){
				if(editorLayer1.entities[i][j]->isStatic){
					level->layer1.entities[i][j] = editorLayer1.entities[i][j]->clone();
				}
			}
		}
	}

	for(unsigned int i = 0; i < editorLayer2.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer2.entities[i].size(); j++){
			if(editorLayer2.entities[i][j] != nullptr){
				if(editorLayer2.entities[i][j]->isStatic && editorLayer2.entities[i][j]->entityType != ENTITY_TYPE::PLAYER ){
					level->layer2.entities[i][j] = editorLayer2.entities[i][j]->clone();
					// std::cout << "mario" << std::endl;
				}
				if(editorLayer2.entities[i][j]->entityType == ENTITY_TYPE::PLAYER){
					Player *p = new Player();
					setDynamicEntityPosition(editorLayer2.entities[i][j], p);
					level->layer2.dynamicEntities.push_back(p);
				}
			}
		}
	}


	for(unsigned int i = 0; i < editorLayer3.entities.size(); i++){
		for(unsigned int j = 0; j < editorLayer3.entities[i].size(); j++){
			if(editorLayer3.entities[i][j] != nullptr){
				if(editorLayer3.entities[i][j]->isStatic){
					level->layer3.entities[i][j] = editorLayer3.entities[i][j]->clone();
				}
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
