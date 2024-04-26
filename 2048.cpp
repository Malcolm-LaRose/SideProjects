#include "Shapes.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include <stdio.h>
#include <memory>
#include <chrono>
#include <random>

// OPENGL NOT ENABLED IN THIS VERSION!


struct MySettings {

	static MySettings& getInstance() {
		static MySettings instance;
		return instance; // Returns a static reference to the MySettings struct
	}


	const int INITIAL_SCREEN_WIDTH = 1920; // Initial screen width, can be overriden if necessary (second MySDL_Renderer constructor)
	const int INITIAL_SCREEN_HEIGHT = 1080;

	const int TARGET_FPS = 180;


	const int gridRows = 4;
	const int gridCols = 4;

	const Shapes::Point gameBoardTopLeft{ 10,10 };

	SDL_Color backgroundColor = { 253, 222, 179, 255 };

private:

	MySettings() {} // Can't delete constructor

};


class MySDL_Renderer {
public:


	MySDL_Renderer(SDL_Window* window) : window(window), renderer(nullptr), SCREEN_WIDTH(settings.INITIAL_SCREEN_WIDTH), SCREEN_HEIGHT(settings.INITIAL_SCREEN_HEIGHT) {
		initSDL();
	}

	MySDL_Renderer(SDL_Window* window, int wid, int hei) : window(window), renderer(nullptr), SCREEN_WIDTH(wid), SCREEN_HEIGHT(hei) {
		initSDL();
	}



	// Disable copy constructor and copy assignment
	MySDL_Renderer(const MySDL_Renderer&) = delete;

	// Disable move constructor and move assignment
	MySDL_Renderer(MySDL_Renderer&&) = delete;

	SDL_Window* getWindow() {
		return window;
	}

	void quitSDL() {
		if (renderer) {
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}
		if (window) {
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		SDL_Quit();
	};


	SDL_Renderer* getRenderer() {
		return renderer;
	}

	int getScWidth() {
		return SCREEN_WIDTH;
	}

	int getScHeight() {
		return SCREEN_HEIGHT;
	}

	void renderAll() {
	
		renderBG();


		presentRender();
		SDL_RenderClear(renderer);
	
	}

private:
	MySettings& settings = MySettings::getInstance();
	SDL_Window* window;
	SDL_Renderer* renderer;

	// SDL_GLContext glContext;


	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


	bool initSDL()
	{
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
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_OPENGL*/);
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
			quitSDL();
		}

		return success;
	}

	void renderBG() {
		Shapes::Point screenTopLeft{ 0, 0 };
		Shapes::Rectangle background(screenTopLeft, SCREEN_WIDTH, SCREEN_HEIGHT, true);
		background.setColor(settings.backgroundColor);

		background.render(renderer);

	}

	void renderGrid() {}

	void renderCells() {}

	void renderScore() {}


	void presentRender() { // Or UpdateWindow?
		// Present the rendered image
		auto startTime = std::chrono::high_resolution_clock::now();
		if (renderer == nullptr) {
			printf("AHHHHHH!\n");
		}

		SDL_RenderPresent(renderer);


		// Calculate time taken to render this frame
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> frameTime = endTime - startTime;

		const int& targetFPS = settings.TARGET_FPS; // Get target FPS from settings

		// If frame rendering took less time than desired frame rate, introduce a delay
		if (frameTime.count() < (1000.0 / targetFPS)) {
			SDL_Delay((Uint32)((1000.0 / targetFPS) - frameTime.count()));
		}
	}

protected:
	MySDL_Renderer() = delete; // Delete default constructor


};

class MySDL_EventHandler { // This class is mostly for neater organization, no real logical/semantic purpose here (can hide messy code away from main game logic)
public:
	MySDL_EventHandler(SDL_Window* window, SDL_Renderer* renderer) : window(window), event(), renderer(renderer) {

	}

	~MySDL_EventHandler() {}

	void pollEvent() {


		while (SDL_PollEvent(&event) != 0) {

			// Log event type
			// printf("Event type: %d\n", event.type);

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {

				// Get coordinates
				std::pair<int, int> mousePosition = getMousePosition();

				printf("Mouse position - x: %d, y: %d\n", mousePosition.first, mousePosition.second);

			}
		}
	}


private:
	SDL_Window* window; // So events can manipulate the window (render is aware of window, should be okay)
	SDL_Event event;
	SDL_Renderer* renderer; // So events can tell the renderer to do something



	std::pair<int, int> getMousePosition() {
		return { event.motion.x, event.motion.y };
	}

};

// Put game classes here!

class Cell { // Cells will have to be dynamically created AND DESTROYED! --> Need all constructors
public:
	Cell() : number(2) {}


private:
	int number; // Default 2 for now, add random chance for 4 later


};

class Grid {
public:

	Grid(int cSpace, int cSize) : rows(4), cols(4), cellSpacing(cSpace), cellSize(cSize) {
		gridData.resize(rows, std::vector<Cell>(cols)); // Make a 4x4 grid (empty, no cells yet) --> Eventually start with 1 cell randomly placed
	}

	void placeCellAt(int row, int col) {
		
	}

	void moveCell() {}


private:
	int rows;
	int cols;

	std::vector<std::vector<Cell>> gridData; // Actual data

	const int cellSpacing;
	const int cellSize;

	MySettings& settings = MySettings::getInstance();

	




};

class Score {




};


static class G2048 { // Just for game functions
public:



private:



};



class MySDL_Wrapper { // This class should collect objects so they're accessible to both the renderer and evHandler, kapische?
public:

	MySDL_Wrapper() : renderer(nullptr), evHandler(nullptr), quit(false) {
		renderer = new MySDL_Renderer(nullptr, settings.INITIAL_SCREEN_WIDTH, settings.INITIAL_SCREEN_HEIGHT);
		evHandler = new MySDL_EventHandler(renderer->getWindow(), renderer->getRenderer());
	}

	~MySDL_Wrapper() {
		quit = true;
		delete renderer;
		delete evHandler;
	}


	void start() {
		if (!renderer || !evHandler) {
			printf("Renderer or EventHandler is null!\n");
			return; // Exit early if renderer or event handler is not initialized
		}

		

		while (!quit) {
			evHandler->pollEvent();

			// Big encapsulating rendering function here

			renderer->renderAll();
			// Check if quit event occurred
			if (SDL_QuitRequested()) {
				quit = true;
			}

		}
		renderer->quitSDL();
	}

	void stop() {
		quit = true;
	}




private:
	MySDL_Renderer* renderer;
	MySDL_EventHandler* evHandler;
	bool quit;

	MySettings& settings = MySettings::getInstance();


};


int main(int argc, char* argv[]) {


	MySDL_Wrapper wrap;
	wrap.start();

	return 0;
}