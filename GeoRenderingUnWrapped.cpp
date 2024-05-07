#include "Shapes.h"
#include "Color.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

// DO THIS FIRST PLEASE, TRUST PAST ME :D
// Fuck SDL in the class! 


const int InitialScreenWidth = 1920;
const int InitialScreenHeight = 1080;

int screenWidth = InitialScreenWidth; // For changing screen dimensions
int screenHeight = InitialScreenHeight;

Shapes::Point screenCenter = { screenWidth / 2, screenHeight / 2 };

const int desiredFPS = 180;




// SDL Functions

void pollEvent(SDL_Event& event) {


	while (SDL_PollEvent(&event) != 0) {

		// Log event type
		printf("Event type: %d\n", event.type);

		if (event.type == SDL_QUIT) {
			exit(0);
		}

	}
}



int main(int argc, char* argv[]) {

	// Init variables

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event{}; // Not sure what list initalization does here but it prevents VS from complaining

	// Init SDL

	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{

		// Create window
		window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, InitialScreenWidth, InitialScreenHeight, SDL_WINDOW_SHOWN );
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}


		}
	}

	if (!success)
	{
		SDL_Quit();
		renderer = nullptr;
		window = nullptr;
	}




	return 0;
}