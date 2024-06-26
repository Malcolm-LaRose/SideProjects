#include "Shapes.h"
#include "Color.h"
// #include "Timer.h"

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

const int desiredFPS = 60;

class MyTimer_us {
public:

	MyTimer_us() : // Multi line constructor
	startTime(std::chrono::steady_clock::now()), // Init with current time --> Class should be init'ed right before main loop
	frameBeginTime(std::chrono::steady_clock::now()), // Init with current time, will be changed immediately
	frameEndTime(std::chrono::steady_clock::now()) // Init with current time, will be changed immediately
	{
		outputTime = startTime;
	}


	std::chrono::steady_clock::time_point t_now() {
		return std::chrono::steady_clock::now(); // Helper function to shorten this line
	}

	std::chrono::duration<double, std::micro> getTotalTimeElapsed() {
		return t_now() - startTime; // Time between now and program start
	}

	std::chrono::duration<double, std::micro>  getOutputTimeElapsed() {
		return t_now() - outputTime;
	}


	void markFrameBeginTime() {
		frameBeginTime = t_now();
	}
	void markFrameEndTime() {
		frameEndTime = t_now();
	}

	std::chrono::duration<double, std::micro> getFrameDuration() {
		return frameDuration;
	}

	void logFPS() {
		computeFrameDuration();

		auto currentTime = t_now();
		if (currentTime - outputTime >= std::chrono::microseconds(250000)) {
			system("cls");
			std::cout << "\rFPS: " << (1000000.0 / frameDuration.count()) << std::endl; // Print FPS
			std::cout << "\rFRAME TIME: " << frameDuration.count() << std::flush; // Print frame time
			std::cout << std::endl; // Move to the next line

			outputTime = currentTime; // Update output time
		}
	}


private:

	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point outputTime;
	std::chrono::steady_clock::time_point frameBeginTime;
	std::chrono::steady_clock::time_point frameEndTime;

	std::chrono::duration<double, std::micro> frameDuration;

	void computeFrameDuration() {
		frameDuration = frameEndTime - frameBeginTime;
	}

};

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
	auto startTime = std::chrono::steady_clock::now();
	if (renderer == nullptr) {
		printf("AHHHHHH!\n");
	}


	SDL_RenderPresent(renderer);


	 // Calculate time taken to render this frame
	 auto endTime = std::chrono::steady_clock::now();
	 std::chrono::duration<double, std::milli> frameTime = endTime - startTime;
	
	 // If frame rendering took less time than desired frame rate, introduce a delay --> FRAME CAP I HAVE NOT FIGURED OUT HOW TO  UNCAP YET
	 if (frameTime.count() < (1000.0 / desiredFPS)) {
		SDL_Delay((Uint32)((1000.0 / desiredFPS) - frameTime.count()));
	 }
}

// My functions

void movingSquare(SDL_Renderer* renderer) { // Static for now but should be moveable next
	double size = 100;

	Shapes::Point sqPos = { screenCenter.x - (size / 2), screenCenter.y - (size / 2) };
	Shapes::Square::Rectangle sq(sqPos, size, true);

	sq.setColor(Color::getSDLColor(Color::PHSORNG));

	sq.render(renderer);
}

void defaultRender(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 80, 80, 88, 255); // Background 
	SDL_RenderClear(renderer);

	movingSquare(renderer);


	presentRender(renderer);
}




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


	MyTimer_us myTimer;


	bool quit = false;

	// std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now(); // Time the program starts the main loop

	while (!quit) {
		// std::chrono::steady_clock::time_point frameBegin = std::chrono::steady_clock::now();
		myTimer.markFrameBeginTime();

		pollEvent(event);
		defaultRender(renderer);

		myTimer.markFrameEndTime();

		myTimer.logFPS();

		// std::chrono::steady_clock::time_point frameEnd = std::chrono::steady_clock::now();
		// std::chrono::duration<double, std::micro> frameTime = (frameEnd - frameBegin);
		//
		// std::chrono::duration<double, std::micro> now = myTimer.getTotalTimeElapsed(); // really total elapsed time since start
		//
		//if (now.count() - myTimer.computeFrameDuration().count() >= 250000) { // Check if 1/4 second has elapsed
		//	if (frameTime.count() <= 1) {
		//		std::cout << "\rFPS: >1000000" << std::flush;
		//	}
		//	else {
		//		system("cls");
		//		std::cout << "\rFPS: " << (1000000.0 / frameTime.count()) << std::endl; // Print FPS
		//		std::cout << "\rFRAME TIME: " << frameTime.count() << std::flush; // Print frame time
		//		std::cout << std::endl; // Move to the next line
		//	}
		//	startTime = std::chrono::steady_clock::now(); // Reset the start time for the next second
		//}

		if (SDL_QuitRequested()) {
			quit = true;
		}
	}

	return 0;
}