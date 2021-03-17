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
#include "timer.h"
#include "music.h"
#include "sound_effects.h"

const float TIME_PER_FRAME = 16; //In milliseconds
const float VOLUME_MULTIPLIER = .5;
const int CHANNELS = 32;

static void printFPS(float FPS, Text fpsText){
	std::string fps = std::to_string(FPS);
	fpsText.renderText(fps);
}

int main(int argc, char**) {
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_VolumeMusic(MIX_MAX_VOLUME * VOLUME_MULTIPLIER);
	Mix_AllocateChannels(CHANNELS);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);            // Initialize SDL2

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

	texturesContainer.initTextureContainer();
	soundsContainer.initSoundsContainer();
	musicContainer.initMusicContainer();

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
	// SDL_Event e;
	bool quit = false;


	//Not currently used
	marioFont.initializeMapofGlyphs();
	Text fpsText(&marioFont);
	fpsText.x = 0;
	fpsText.y = 0;
	fpsText.size = 16;

	Timer timer;

	Music overWorldTheme;
	overWorldTheme.music = musicContainer.overWorldTheme;
	Music undergroundTheme;
	undergroundTheme.music = musicContainer.undergroundTheme;



	while( !quit )
	{


		while( SDL_PollEvent( &globalEvent ) != 0 )
		{
			//User requests quit
			if (globalEvent.type == SDL_WINDOWEVENT
				&& globalEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				quit = true;
			}
			switch( globalEvent.type ){
	          	case SDL_KEYDOWN:
	               switch( globalEvent.key.keysym.sym ){
	                    case SDLK_SPACE:
	                        testingLevel = !testingLevel;
					    if(testingLevel){
						    	overWorldTheme.play();
						    	editedLevel.resetCamera();
						     editor.loadEntitiesToScene();
						}
					    else {
						    Mix_HaltMusic();
						    editedLevel.unloadEntities();
					    }
	                        break;					  
				}
				break;
				case SDL_MOUSEWHEEL:
					// std::cout << "moving" << std::endl;
					if(globalEvent.wheel.y > 0){
						editor.layerBeingEdited += 1;
						editor.setLayerBeingEdited();
   					}
					else if(globalEvent.wheel.y < 0){
						editor.layerBeingEdited -= 1;
						editor.setLayerBeingEdited();
					}
					break;
	        }



		}



		SDL_Delay(TIME_PER_FRAME);
		// Execute the main gameloop every 16ms

		// std::cout << timer.timeSum << std::endl;
		// FPS = 1/timePerFrameSum;
		// std::cout << timePerFrameSum << std::endl;


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
			editedLevel.updateScene(TIME_PER_FRAME / 1000.f);
			editedLevel.checkCollisions();
			SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
			SDL_RenderClear( renderer );
			editedLevel.drawScene();
			// printFPS(FPS, fpsText );
			SDL_RenderPresent( renderer );
		}



		// finalTime = (float)SDL_GetTicks() / 1000.f;

		// SDL_Delay(1);
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
    Mix_CloseAudio();
    Mix_Quit();
    return 0;
}
