#include "Shapes.h"
#include "Color.h"
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

	const float initScreenWidth = 1920.0;
	const float initScreenHeight = 1080.0;

	const Shapes::Point screenCenter = { initScreenWidth / 2 , initScreenHeight / 2 };

	const std::string windowTitle = "MyWindow";

	const SDL_Color bgColor = Color::getSDLColor(Color::EIGENGRAU);

	const int frameRateCap = 600;




};

class MyDefaultObject {
public:
	MyDefaultObject() : size(200), defaultRect({ settings.screenCenter.x - (size / 2), settings.screenCenter.y - (size / 2) }),
		rectPos({ settings.screenCenter.x - (size / 2), settings.screenCenter.y - (size / 2) }),
		sq(rectPos, size, true) {
		defaultRectColor = Color::getSDLColor(Color::PHSORNG);
		sq.setColor(defaultRectColor);
	}

	void render(SDL_Renderer* renderer) {
		sq.render(renderer);
	}

private:
	const MySettings& settings = MySettings::getInstance();
	float size;
	SDL_Color defaultRectColor;
	SDL_FRect defaultRect;
	Shapes::Point rectPos;
	Shapes::Square::Rectangle sq;
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

	void update() {
		count++; // Game frame counter



	}

	void render() {
		SDL_RenderClear(renderer);
		renderBG();

		// Add stuff to render
		defaultRectangle.render(renderer);

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

	MyDefaultObject defaultRectangle;
	

	int screenWidth; // Can change with user input
	int screenHeight;

	void renderBG() {
		SDL_RenderClear(renderer);

		Shapes::Point screenTopLeft{ 0, 0 };
		Shapes::Rectangle background(screenTopLeft, screenWidth, screenHeight, true);
		background.setColor(settings.bgColor);

		background.render(renderer);

	}

	void defaultRender() {
		
	}



	// Internal member functions




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
		wrapper->update(); // Game logic
		wrapper->render(); // Rendering

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