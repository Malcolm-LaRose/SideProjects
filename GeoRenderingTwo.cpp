#include "Shapes.h"
#include "Color.h"
#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <chrono>
#include <sstream> 
#include <string> // Inherited from sstream
#include <iostream>
#include <thread>
#include <stdio.h> // Inherited from SDL.h

#include <windows.h>

struct MySettings {

	static MySettings& getInstance() {
		static MySettings instance;
		return instance; // Returns a static reference to the MySettings struct
	}

	const int initScreenWidth = 1920;
	const int initScreenHeight = 1080;

	const std::string windowTitle = "MyWindow";

	const SDL_Color bgColor = Color::getSDLColor(Color::EIGENGRAU);

	const int frameRateCap = 60;


};

class MyObject {};

class MySDLWrapper { // Should be turned into GameX or SimX when implemented
public:

	MySDLWrapper() : screenWidth(settings.initScreenWidth), screenHeight(settings.initScreenHeight) {
		init(); // Automatically runs init when instantiating MySDLWrapper
	}


	void init() {
		running = true;
	
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			running = false;
		}
		else
		{

			// Create window
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				running = false;
			}
			else
			{
				// Create renderer for window
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					running = false;
				}

				// Initialize SDL_ttf
				else if (TTF_Init() != 0) {
					printf("SDL_ttf initialization failed");
					running = false;
				}

				// Init background
				SDL_SetRenderDrawColor(renderer, settings.bgColor.r, settings.bgColor.g, settings.bgColor.b, settings.bgColor.a);



			}
		}

		if (!running)
		{
			SDL_Quit();
			renderer = nullptr;
			window = nullptr;
		}

	}

	void handleEvents() {
		SDL_Event event;
		SDL_PollEvent(&event); // Pointer to event

		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			// Add cases

			default:
				break;
		
		}
	
	}

	void update() {
		count++; // Game frame counter
		// std::cout << count << std::endl;


	
	}

	void render() {
		SDL_RenderClear(renderer);

		// Add stuff to render
	

		SDL_RenderPresent(renderer);
	}

	void clean() {
	
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		std::cout << "Cleanup complete!";

	}

	bool isRunning() {
		return running;
	}



private:
	const MySettings& settings = MySettings::getInstance();

	bool running = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int screenWidth; // Can change with user input
	int screenHeight;

	uint64_t count = 0;


	// Internal member functions




};





int main(int argc, char* argv[]) {

	// Object Instantiation

	MySDLWrapper* wrapper = nullptr; // Wrapper points toward the MySDLWrapper class

	wrapper = new MySDLWrapper;

	MyTimer_us* timer = nullptr;

	timer = new MyTimer_us;


	// Main loop
	while (wrapper->isRunning()) {
		timer->markFrameBeginTime();
	
		wrapper->handleEvents(); // Event handling
		wrapper->update(); // Game logic
		wrapper->render(); // Rendering

		timer->markFrameEndTime();
		timer->logFPS();
	}

	// Quit
	wrapper->clean();
	timer = nullptr;
	wrapper = nullptr;

	return 0;
}