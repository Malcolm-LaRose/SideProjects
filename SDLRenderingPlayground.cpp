#include <SDL.h>
#include <stdio.h>
#include <memory>

class MySDL_Renderer {
public:
	MySDL_Renderer(SDL_Window* window) : window(window), renderer(nullptr), SCREEN_WIDTH(0), SCREEN_HEIGHT(0) {
		initSDL();
	}

	MySDL_Renderer(SDL_Window* window, int wid, int hei) : window(window), renderer(nullptr), SCREEN_WIDTH(wid), SCREEN_HEIGHT(hei) {
		initSDL();
	}

	// ~MySDL_Renderer() : {}

	// Disable copy constructor
	MySDL_Renderer(const MySDL_Renderer&) = delete;

	// Disable move constructor
	MySDL_Renderer(MySDL_Renderer&&) = delete;

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
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
					// Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				}

			}
		}

		return success;
	}

	void quitSDL() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	};

	void presentRender() {
		// Present the rendered image
		SDL_RenderPresent(renderer);
	}

	void updateWindow() {
	
	}





private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


};



int main(int argc, char* argv[]) {

	// MySDL_Renderer* myRenderer = new MySDL_Renderer(nullptr); // Leaky! Try using a smart pointer

	std::unique_ptr<MySDL_Renderer> myRenderer(new MySDL_Renderer(nullptr, 1000, 1000));

	myRenderer->presentRender();

	return 0;
}