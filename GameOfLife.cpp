#include <SDL.h>
#include <SDL_syswm.h>
#include <list>

class GameOfLife {

public:


private:


// End of GOL class
};




void backgroundRendering(int newWidth, int newHeight, SDL_Renderer* renderer) {

    // Recalculate the dimensions of the border rectangle
    SDL_Rect fullBorder = { 6, 6, newWidth - 312, newHeight - 12 };

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render the border rectangle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &fullBorder);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}


int main(int argc, char* args[])
{
    // DPI awareness
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN), &wmInfo);
    SetProcessDPIAware(); // Or use SetProcessDpiAwareness() for more control


    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    const int screenWidth = 3840; // Width of your 4K screen
    const int screenHeight = 2160; // Height of your 4K screen
    const int windowWidth = 1920; // Width of your window
    const int windowHeight = 1080; // Height of your window
    const int centerX = (screenWidth - windowWidth) / 2;
    const int centerY = (screenHeight - windowHeight) / 2;
    const int borderWidth = 6;

    // Create a window
    SDL_Window* window = SDL_CreateWindow("2D Grid", centerX, centerY, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Check if the window was created successfully
    if (!window) {
        // Handle window creation failure
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Check if the renderer was created successfully
    if (!renderer) {
        // Handle renderer creation failure
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 1;
    }

    // Main loop
    bool isRunning = true;
    while (isRunning) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Handle mouse button down event
                break;
            case SDL_MOUSEBUTTONUP:
                // Handle mouse button up event
                break;
            case SDL_MOUSEMOTION:
                // Handle mouse motion event
                break;
                // Add more event handling as needed
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Update rendering logic or viewport here
                    int newWidth = event.window.data1;
                    int newHeight = event.window.data2;
                    printf("Window resized to %dx%d\n", newWidth, newHeight);

                    SDL_RenderSetViewport(renderer, NULL);
                    SDL_RenderSetLogicalSize(renderer, newWidth, newHeight);
                }
                break;
            }
        }

        backgroundRendering(windowWidth, windowHeight, renderer);

        // Render your 2D grid here
            // Set of rectangles representing the grid
            // Set spacing and width/height to be proportional to window size

        const int rows = 100;
        const int cols = 100;

        //for (int i = 0; i < rows;)



        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}