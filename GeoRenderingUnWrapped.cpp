#include "Shapes.h"
#include "Color.h"
#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <chrono>
#include <sstream>
#include <iostream>
#include <thread>
#include <windows.h>


const int InitialScreenWidth = 1920;
const int InitialScreenHeight = 1080;

int screenWidth = InitialScreenWidth; // For changing screen dimensions
int screenHeight = InitialScreenHeight;

Shapes::Point screenCenter = { screenWidth / 2, screenHeight / 2 };

const int desiredFPS = 360;

Uint32 myTime = 0;


// Calculate time taken to render this frame






// SDL Functions

void pollEvent(SDL_Event& event) {


	while (SDL_PollEvent(&event) != 0) {

		// Log event type
		// printf("Event type: %d\n", event.type);

		if (event.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}

	}
}

void presentRender(SDL_Renderer* renderer) { // Or UpdateWindow?
	// Present the rendered image
	auto startTime = std::chrono::high_resolution_clock::now();
	if (renderer == nullptr) {
		printf("AHHHHHH!\n");
	}


	SDL_RenderPresent(renderer);


	// Calculate time taken to render this frame
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> frameTime = endTime - startTime;

	// If frame rendering took less time than desired frame rate, introduce a delay --> FRAME CAP
	if (frameTime.count() < (1000.0 / desiredFPS)) {
		SDL_Delay((Uint32)((1000.0 / desiredFPS) - frameTime.count()));
	}
}

// My functions

void defaultRender(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 80, 80, 88, 255); // Background 
	SDL_RenderClear(renderer);

	// Rendering other stuff
	int size = 100;

	Shapes::Point rectPos{ (screenWidth - size) / 2, (screenHeight - size) / 2 }; // Top left of rectangle with size 100 centered on the screen center
	Shapes::Square::Rectangle sq(rectPos, size, true);
	sq.setColor(Color::getSDLColor(Color::MAGENTA));
	sq.render(renderer);

	sq.setColor(Color::getSDLColor(Color::PHSORNG));
	sq.render(renderer);


	presentRender(renderer);
}


void logFPS() {}




int main(int argc, char* argv[]) {

	// Init variables

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event{}; // Not sure what list initalization does here but it prevents VS from complaining

	std::stringstream timeText;

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
		window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, InitialScreenWidth, InitialScreenHeight, SDL_WINDOW_SHOWN);
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

			// Initialize SDL_ttf
			else if (TTF_Init() != 0) {
				printf("SDL_ttf initialization failed");
				SDL_Quit();
				return 1;
			}
		}
	}

	if (!success)
	{
		SDL_Quit();
		renderer = nullptr;
		window = nullptr;
	}

	bool quit = false;

	double startTime = SDL_GetTicks(); // Time the program starts the main loop
	double prevFrameTime = 0;

	while (!quit) {
		double frameBegin = SDL_GetTicks();

		pollEvent(event);
		defaultRender(renderer);

		double frameEnd = SDL_GetTicks();
		double frameTime = frameEnd - frameBegin;

		if (SDL_GetTicks() - startTime >= 250) { // Check if one second has elapsed
			if (frameTime <= 1) {
				std::cout << "\rFPS: >1000" << std::flush;
			}
			else {
				system("cls");
				std::cout << "\rFPS: " << (1000.0 / frameTime) << std::endl; // Print FPS
				std::cout << "\rFRAME TIME: " << frameTime << std::flush; // Print frame time
				std::cout << std::endl; // Move to the next line
			}
			startTime = SDL_GetTicks(); // Reset the start time for the next second
		}

		if (SDL_QuitRequested()) {
			quit = true;
		}
	}

	return 0;
}