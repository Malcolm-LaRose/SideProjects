#include "Shapes.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <stdio.h>
#include <memory>
#include <chrono>

// OPENGL NOT ENABLED IN THIS VERSION!

class MySDL_Renderer {
public:
	MySDL_Renderer(SDL_Window* window) : window(window), renderer(nullptr), INITIAL_SCREEN_WIDTH(100), INITIAL_SCREEN_HEIGHT(100), targetFPS(60) {
		initSDL();
	}

	MySDL_Renderer(SDL_Window* window, int wid, int hei) : window(window), renderer(nullptr), INITIAL_SCREEN_WIDTH(wid), INITIAL_SCREEN_HEIGHT(hei), targetFPS(60) {
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
			/*SDL_GL_DeleteContext(glContext);*/
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		SDL_Quit();
	};


	SDL_Renderer* getRenderer() {
		return renderer;
	}

	// Add rendering functions here, or, have a way for another class to add something to the renderer here

	void drawBackground() {
	
	}

	int getScWidth() {
		return SCREEN_WIDTH;
	}

	int getScHeight() {
		return SCREEN_HEIGHT;
	}

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

		// If frame rendering took less time than desired frame rate, introduce a delay
		if (frameTime.count() < (1000.0 / targetFPS)) {
			SDL_Delay((Uint32)((1000.0 / targetFPS) - frameTime.count()));
		}
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	// SDL_GLContext glContext;

	const int INITIAL_SCREEN_WIDTH;
	const int INITIAL_SCREEN_HEIGHT;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	int targetFPS;


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
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_OPENGL*/);
			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SCREEN_HEIGHT = INITIAL_SCREEN_HEIGHT;
				SCREEN_WIDTH = INITIAL_SCREEN_WIDTH;
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

	//bool initOpenGL() {
	//	// Initialization flag
	//	bool success = true;

	//	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	//	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	//	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	//	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
	//	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//	glContext = SDL_GL_CreateContext(window);

	//	SDL_GL_MakeCurrent(window, glContext);

	//	if (glContext == nullptr) {
	//		// OpenGL context creation failed
	//		printf("Failed to create OpenGL context: %s\n", SDL_GetError());
	//		success = false;
	//	}

	//	return success;

	//}

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

				if () {
					
				}

			}


		}
	}


private:
	SDL_Window* window; // So events can manipulate the window (render is aware of window, should be okay)
	SDL_Event event;
	SDL_Renderer* renderer;




	std::pair<int, int> getMousePosition() {
		return { event.motion.x, event.motion.y };
	}

};

class MySDL_Wrapper {
public:

	MySDL_Wrapper() : renderer(nullptr), evHandler(nullptr), quit(false) {
		renderer = new MySDL_Renderer(nullptr, 1000, 1000);
		evHandler = new MySDL_EventHandler(renderer->getWindow(), renderer->getRenderer());
	}

	~MySDL_Wrapper() {
		quit = true;
		delete renderer;
		delete evHandler;
	}

	void defaultRender() {

		SDL_SetRenderDrawColor(renderer->getRenderer(), 80, 80, 88, 255); // Background 
		SDL_RenderClear(renderer->getRenderer());

		// Rendering other stuff
		int size = 100;

		Point rectPos{ (renderer->getScWidth() - size) / 2, (renderer->getScHeight() - size) / 2 }; // Center pos
		Square::Rectangle sq(rectPos, size, true);
		sq.setColor(Color::getSDLColor(Color::MAGENTA));
		sq.render(renderer->getRenderer());

		sq.setColor(Color::getSDLColor(Color::PHSORNG));
		sq.render(renderer->getRenderer());


		renderer->presentRender();
	}


	void start() {
		if (!renderer || !evHandler) {
			printf("Renderer or EventHandler is null!\n");
			return; // Exit early if renderer or event handler is not initialized
		}

		defaultRender();

		while (!quit) {
			evHandler->pollEvent();

			renderer->presentRender();
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


};

// Do TicTacToe but rendered!

class TicTacToe {



};


int main(int argc, char* argv[]) {


	MySDL_Wrapper wrap;
	wrap.start();

	return 0;
}