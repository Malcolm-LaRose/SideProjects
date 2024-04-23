#include <SDL.h>
#include <stdio.h>
#include <memory>


// OPENGL NOT ENABLED IN THIS VERSION!

class MySDL_Renderer {
public:
	MySDL_Renderer(SDL_Window* window) : window(window), renderer(nullptr), SCREEN_WIDTH(100), SCREEN_HEIGHT(100) {
		initSDL();
	}

	MySDL_Renderer(SDL_Window* window, int wid, int hei) : window(window), renderer(nullptr), SCREEN_WIDTH(wid), SCREEN_HEIGHT(hei) {
		initSDL();
	}

	~MySDL_Renderer() {
		quitSDL();
	}

	// Disable copy constructor and copy assignment
	MySDL_Renderer(const MySDL_Renderer&) = delete;
	MySDL_Renderer& operator=(const MySDL_Renderer&) = delete;

	// Disable move constructor and move assignment
	MySDL_Renderer(MySDL_Renderer&&) = delete;
	MySDL_Renderer& operator=(MySDL_Renderer&&) = delete;

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

	void presentRender() { // Or UpdateWindow?
		// Present the rendered image
		SDL_RenderPresent(renderer);
	}

	SDL_Renderer* getRenderer() {
		return renderer;
	}

	// Add rendering functions here, or, have a way for another class to add something to the renderer here





private:
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
				else {
					SDL_RenderClear(renderer);

					// Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

					// Initialize OpenGL
					/*success = initOpenGL();*/

				}

			}
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
	MySDL_EventHandler() : window(nullptr), quit(false), event() {

	}

	~MySDL_EventHandler() {}

	void setWindow(SDL_Window* win) {
		window = win;
	}

	void pollEvent() {
		while (SDL_PollEvent(&event) != 0) {

			// Log event type
			// printf("Event type: %d\n", event.type);


			// If user quits the window, set quit flag to true
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {

				// Get coordinates
				std::pair<int, int> mousePosition = getMousePosition();

				printf("Mouse position - x: %d, y: %d\n", mousePosition.first, mousePosition.second);
			}


		}
	}

	bool isQuit() {
		return quit;
	}

private:
	SDL_Window* window; // So events can manipulate the window (render is aware of window, should be okay)
	SDL_Event event;

	bool quit;



	std::pair<int, int> getMousePosition() {
		return { event.motion.x, event.motion.y };
	}

};


int main(int argc, char* argv[]) {


	std::unique_ptr<MySDL_EventHandler> myHandler(new MySDL_EventHandler());

	// MySDL_Renderer* myRenderer = new MySDL_Renderer(nullptr); // Leaky! Try using a smart pointer

	// std::unique_ptr<MySDL_Renderer> myRenderer(new MySDL_Renderer(nullptr, 1000, 1000)); // Very smart! i dunno

	MySDL_Renderer myRenderer = MySDL_Renderer(nullptr, 1000, 1000);

	myHandler->setWindow(myRenderer.getWindow()); // Make myHandler aware of the window in myRenderer

	bool quit = false;


	myRenderer.presentRender();

	while (!quit) {
		myHandler->pollEvent();
		myRenderer.presentRender();

		if (myHandler->isQuit()) {
			quit = true;
		}

	}

	myRenderer.quitSDL();


	return 0;
}
