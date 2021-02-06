#include <string>
#include <iostream>
#include <vector>
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
	
	// SDL_SetWindowSize(window, 1280, 720);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);	
	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	
	SDL_Rect camera;
	camera.x = 0;
	camera.y = 0;
	camera.w = 1280;
	camera.h = 720;
	SDL_Texture *texture = loadTexture("assets/textures/mario.png");
	// for(int i = 0; i < 100; i++){
		// Player player;
		// player.sprite.texture = texture;
		// player.sprite.boundingBox.x = i;
		// player.sprite.boundingBox.y = i + 1;
		// player.sprite.boundingBox.w = 80;
		// player.sprite.boundingBox.h = 80;
		
		// sprites.push_back(player);
	// }
	// Scene scene1;
	
	// int *w;
	// int *h;
	// Uint32 *format;
	// SDL_QueryTexture(texture, format, NULL, w, h);
	// std::cout << *w << "  " << *h << std::endl; 
	
	Player player;
	player.x = 30;
	player.y = 0;
	player.sprite.texture = texture;
	player.sprite.boundingBox.w = 64;
	player.sprite.boundingBox.h = 64;
	player.clippingBox.x = 0;
	player.clippingBox.y = 0;
	player.clippingBox.w = 16;// THIS WILL BE CLEANED UP EVENTUALLY. THIS WAS ONLY FOR TESTING
	player.clippingBox.h = 16;
	
	Ground brick;
	// brick.x = 30;
	// brick.y = 0;
	brick.sprite.texture = texture;
	// brick.sprite.boundingBox.x = 32;
	// brick.sprite.boundingBox.y = 32;
	
	

	
	// std::cout << "TEST" << std::endl;
	LevelEditor editor;
	editor.level.camera = &camera;
	editor.layerBeingEdited = 0;
	editor.setTileMapBeingEdited();
	editor.selectedEntity = &brick;
	// editor.level.setScale(xScale, yScale);
	
	// scene1.background.addEntityByTile(&tile1);
	// scene1.collideable.addEntityByTile(&player);
	
	
	
	SDL_Event e;
	bool quit = false;	
	// int countedFrames = 0;
		
	// auto begin = std::chrono::high_resolution_clock::now();
	// auto end = std::chrono::high_resolution_clock::now();
	float x;
	float y;
	while( !quit )
	{
		// auto startingTime = std::chrono::system_clock::now();		
		float startingTime = (float)SDL_GetTicks() / 1000.f;
		float FPS = 1.0f / deltaT;		
		// std::cout << "ms: " << deltaTime * 1000.f << std::endl;
		// std::cout << "FPS: " << FPS << std::endl;		
		
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if (e.type == SDL_WINDOWEVENT
				&& e.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				quit = true;
			}	
			// if (e.type == SDL_MOUSEBUTTONDOWN){
				// std::cout << e.window.windowID << std::endl;
				// SDL_RaiseWindow(SDL_GetWindowFromID(e.window.windowID));
			// }
		}		
		editor.setSelectedEntity();
		editor.setTileOnClick();
		editor.deleteTileOnClick();
		
		
		// //ALL OF THIS WAS ONLY FOR TESTING. THIS NEEDS TO BE REMOVED. 
		// //MOVE THIS TO A NEW FILE FOR CAMERA RELATED FUNCTIONS
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
		
		
		editor.level.updateScene(deltaT);
				
		SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
		SDL_RenderClear( renderer );
		editor.level.drawScene();
		editor.drawEditorWindow();
		SDL_RenderPresent( renderer );
				
		
		float finalTime = (float)SDL_GetTicks() / 1000.f;		
		deltaT = finalTime - startingTime;
	}
 
    // Clean up
	//Destroy window and renderer.
	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
	

    //Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
    return 0;
}




