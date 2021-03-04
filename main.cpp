#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <chrono>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "timer.h"
#include "global_variables.h"
#include "player.h"
#include "texture.h"
#include "tile.h"
#include "tile_map.h"
#include "scene.h"
#include "level_editor.h"
#include "renderer.h"
#include "text.h"

static void printFPS(float FPS, Text fpsText){
	std::string fps = std::to_string(FPS);
	fpsText.renderText(fps);
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // initializeWindow(window, renderer, "Main Window");
	// initializeWindow(editorWindow, editorRenderer, "Editor Window");
	window = SDL_CreateWindow(
        "Main window",                  // window title
        SDL_WINDOWPOS_CENTERED,           // initial x position
        SDL_WINDOWPOS_CENTERED,           // initial y position
        WINDOW_WIDTH,                               // width, in pixels
        WINDOW_HEIGHT,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );


	// SDL_SetWindowSize(window, 1440, 900);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	// SDL_MaximizeWindow(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	textures.initTextureContainer();

	// SDL_RenderSetLogicalSize(renderer, 1280, 480);
	// int rendererX = getRendererWidth();
	// int rendererY = getRendererHeight();
	// int RENDERER_WIDTH = rendererX;
	// int RENDERER_HEIGHT = rendererY;
	// screenSurface = SDL_GetWindowSurface(window);
	if (renderer == NULL){
		std::cout << "Window couldn't be created" << std::endl;
	}

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
    }

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return 1;
	}

	bool testingLevel = false;
	Scene editedLevel;
	LevelEditor editor;
	editor.level = &editedLevel;
	editor.setTileMapBeingEdited();

	SDL_Event e;
	bool quit = false;

	GlyphsMap font;
	Text fpsText(&font);
	fpsText.x = 0;
	fpsText.y = 0;
	fpsText.size = 16;

	double startingTime = 0;
	double finalTime = 0;
 	double timePerFrameSum = 0;
	// double FPS = 0;

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if (e.type == SDL_WINDOWEVENT
				&& e.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				quit = true;
			}
			switch( e.type ){
	            /* Look for a keypress */
	          	case SDL_KEYDOWN:
	                /* Check the SDLKey values and move change the coords */
	               switch( e.key.keysym.sym ){
	                    case SDLK_SPACE:
	                        testingLevel = !testingLevel;
					    // timePerFrameSum = 0;
					    if(testingLevel){
						     editor.loadEntitiesToScene();
							editedLevel.resetCamera();
						}
					    else editedLevel.unloadEntities();
	                        break;
				}
				break;
				case SDL_MOUSEWHEEL:
					// std::cout << "moving" << std::endl;
					if(e.wheel.y > 0){
						editor.layerBeingEdited += 1;
						editor.setLayerBeingEdited();
   					}
					else if(e.wheel.y < 0){
						editor.layerBeingEdited -= 1;
						editor.setLayerBeingEdited();
					}
					break;
			// 		case SDL_WINDOWEVENT:  {
	          // if (e.window.windowID == windowID)  {
	          //   			switch (e.window.event)  {
			// 	              case SDL_WINDOWEVENT_MOVED:  {
			// 				    timePerFrameSum = 0;
			// 				    startingTime = 0;
			// 				    finalTime = 0;
			// 				    deltaT = 0;
			// 				    break;
			// 				}
	          // 			}
	          // 			break;
	        	// 		}
			// }
	        }

		}

		//Here begins draw and update loop
		startingTime = (float)SDL_GetTicks() / 1000.f; // We should get the time with a method that brings us better precision
		deltaT = startingTime - finalTime;
		timePerFrameSum += deltaT;
		finalTime = startingTime;

		//We do this because while we are moving the window the time counter keeps counting and it keeps going till you reac seconds
		//and it causes the player to get updated by a big amount of deltaT causing it to skip collisions
		//There should be a better way of doing this by detecting when the window is being moved
		if(timePerFrameSum > .018) timePerFrameSum = 0;

		// Execute the main gameloop every 16ms
		if(timePerFrameSum >= deltaTfixed){
			// FPS = 1/timePerFrameSum;
			// std::cout << timePerFrameSum << std::endl;

			timePerFrameSum = 0;



			if(!testingLevel){
				editor.setSelectedEntity();
				editor.setTileOnClick();
				editor.deleteTileOnClick();
				editor.udpateEditorLevel();

				SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
				SDL_RenderClear( renderer );
				editor.drawEditorLevel();
				editor.drawEditorWindow();
				editor.drawLayerText();

				// printFPS(FPS, fpsText);

				SDL_RenderPresent( renderer );

			}

			if(testingLevel){
				editedLevel.updateScene(deltaTfixed);
				editedLevel.checkCollisions();
				SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
				SDL_RenderClear( renderer );
				editedLevel.drawScene();
				// printFPS(FPS, fpsText );
				SDL_RenderPresent( renderer );
			}


		}

	}

    // Clean up
	//Destroy window and renderer.
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    // SDL_DestroyTexture(Tile::texture);

    window = NULL;
    renderer = NULL;


    //Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
    return 0;
}
