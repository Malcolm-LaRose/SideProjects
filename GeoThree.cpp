// #include "Shapes.h"
#include "color.h"
#include "Timer.h" // USING SDL UNTIL THIS IS WORKING PROPERLY

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

	const int initScreenWidth = 1920.0;
	const int initScreenHeight = 1080.0;

	const SDL_Point screenCenter = { initScreenWidth / 2 , initScreenHeight / 2 };
	
	const std::string windowTitle = "MyWindow";

	const SDL_Color bgColor = Color::getSDLColor(Color::EIGENGRAU);

	const int frameRateCap = 600;




};

struct myRectangle {





};




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

	void update(Uint32 frameTime) {
		// Perform other updates here as needed




		count++;
	}


	void render(Uint32 frameTime) {
		SDL_RenderClear(renderer);
		renderBG();

		// Add stuff to render

		SDL_RenderPresent(renderer);

		// capFPS(settings.frameRateCap, MyTimer_us::getFrameDuration());
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

	uint64_t getCount() {
		return count;
	}


	uint64_t count = 0;

private:
	const MySettings& settings = MySettings::getInstance();

	bool running = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;


	int screenWidth; // Can change with user input
	int screenHeight;


	// Internal member functions

	void renderBG() {
		SDL_RenderClear(renderer);

		SDL_Point screenTopLeft{ 0, 0 };
		SDL_FRect background{ screenTopLeft.x, screenTopLeft.y, screenWidth, screenHeight };
		SDL_SetRenderDrawColor(renderer, settings.bgColor.r, settings.bgColor.g, settings.bgColor.b, settings.bgColor.a);

		SDL_RenderPresent(renderer);

	}

	//void moveAtSpeed(float dx, float dy, Uint32 frameTime) {
	//	Uint32 prevFrameTime = 0; // Static variable to store previous frame time

	//	float deltaTime = (frameTime - prevFrameTime); // Calculate delta time in seconds
	//	prevFrameTime = frameTime; // Update previous frame time

	//	// Calculate movement based on delta time
	//	dx = 1000.0f * deltaTime; // Adjust the value as needed for desired speed
	//	dy = 1000.0f * deltaTime; // Adjust the value as needed for desired speed
	//	// defaultRectangle.moveObject(dx, dy); // Move the object based on scaled movement


	//}

};







int main(int argc, char* argv[]) {

	// Object Instantiation

	Uint32 frameStart = 0;
	int frameTime = 0;

	const MySettings& settings = MySettings::getInstance();

	MySDLWrapper* wrapper = nullptr; // Wrapper points toward the MySDLWrapper class

	wrapper = new MySDLWrapper;

	MyTimer_us* timer = nullptr;

	timer = new MyTimer_us;


	// Main loop
	while (wrapper->isRunning()) {
		// timer->markFrameBeginTime();

		frameStart = SDL_GetTicks();

		wrapper->handleEvents(); // Event handling
		wrapper->update(frameTime); // Game logic
		wrapper->render(frameTime); // Rendering

		// timer->markFrameEndTime(); 
		// timer->logFPS();
		// system("cls");
		// std::cout << "\rAVG SDL FPS: " << (wrapper->getCount() * 1000) / SDL_GetTicks() << std::endl; --> Agrees with below
		std::cout << "\rAVG FPS: " << (wrapper->getCount() * 1000000) / timer->getTotalTimeElapsed().count() << std::flush;

		frameTime = SDL_GetTicks() - frameStart;

		if ((1000 / settings.frameRateCap) > frameTime) {
			SDL_Delay((1000 / settings.frameRateCap) - frameTime);
		}


	}

	// Quit
	wrapper->clean();
	timer = nullptr;
	wrapper = nullptr;

	return 0;

}