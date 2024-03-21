#include <SDL.h>
#include <SDL_syswm.h>
#include <list>

class GameOfLife {

public:
    void eventHandler(bool isRunning) {
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
    }

    void initWindow() {
        // Create a window
        window = SDL_CreateWindow("2D Grid", centerX, centerY, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        // Check if the window was created successfully
        if (!window) {
            // Handle window creation failure
            SDL_Log("Failed to create window: %s", SDL_GetError());
            exit(1);
        }
    }
    void initRenderer() {
        // Create a renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Check if the renderer was created successfully
        if (!renderer) {
            // Handle renderer creation failure
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            exit(1);
        }
    }
    void fullInitialization() {
        // DPI awareness
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN), &wmInfo);
        SetProcessDPIAware(); // Or use SetProcessDpiAwareness() for more control


        // Initialize SDL
        SDL_Init(SDL_INIT_VIDEO);

        void initWindow();
        void initRenderer();

    }
    
    void backgroundRender() {
        // Recalculate the dimensions of the border rectangle
        SDL_Rect fullBorder = { 6, 6, windowWidth - 312, windowHeight - 12 };

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background
        SDL_RenderClear(renderer); 

        // Render the border rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &fullBorder);

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }
    void updateRender() {} // Maybe?

    void renderingLoop() {}
    void gameLoop() {
        // Main loop
        bool isRunning = true;

        // Initialization

        while (isRunning) {
            eventHandler(isRunning);
            }

            backgroundRender();

            // Render your 2D grid here
                // Set of rectangles representing the grid
                // Set spacing and width/height to be proportional to window size


            // Present the rendered frame
            //SDL_RenderPresent(renderer);
        }

    void gameStart() {
        fullInitialization();
        gameLoop();
        cleanUp();
    }
    void cleanUp() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


private:
    // SDL Stuff
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect borderRect;

    // Important numerical values
    const int screenWidth = 3840;
    const int screenHeight = 2160;
    const int borderSize = 6; //px
    int windowWidth;
    int windowHeight;
    int centerX = (screenWidth - windowWidth) / 2;
    int centerY = (screenHeight - windowHeight) / 2;

    int numCellsX;
    int numCellsY;


// End of GOL class
};




int main(int argc, char* args[])
{

    //const int screenWidth = 3840; // Width of your 4K screen
    //const int screenHeight = 2160; // Height of your 4K screen
    //const int windowWidth = 1920; // Width of your window
    //const int windowHeight = 1080; // Height of your window
    //const int centerX = (screenWidth - windowWidth) / 2;
    //const int centerY = (screenHeight - windowHeight) / 2;
    //const int borderWidth = 6;

    //// DPI awareness
    //SDL_SysWMinfo wmInfo;
    //SDL_VERSION(&wmInfo.version);
    //SDL_GetWindowWMInfo(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN), &wmInfo);
    //SetProcessDPIAware(); // Or use SetProcessDpiAwareness() for more control


    //// Initialize SDL
    //SDL_Init(SDL_INIT_VIDEO);

    //// Create a window
    //SDL_Window* window = SDL_CreateWindow("2D Grid", centerX, centerY, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    //// Check if the window was created successfully
    //if (!window) {
    //    // Handle window creation failure
    //    SDL_Log("Failed to create window: %s", SDL_GetError());
    //    return 1;
    //}

    //// Create a renderer
    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //// Check if the renderer was created successfully
    //if (!renderer) {
    //    // Handle renderer creation failure
    //    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    //    return 1;
    //}

    //// Main loop
    //bool isRunning = true;
    //while (isRunning) {
    //    // Handle events
    //    SDL_Event event;
    //    while (SDL_PollEvent(&event)) {
    //        switch (event.type) {
    //        case SDL_QUIT:
    //            isRunning = false;
    //            break;
    //        case SDL_MOUSEBUTTONDOWN:
    //            // Handle mouse button down event
    //            break;
    //        case SDL_MOUSEBUTTONUP:
    //            // Handle mouse button up event
    //            break;
    //        case SDL_MOUSEMOTION:
    //            // Handle mouse motion event
    //            break;
    //            // Add more event handling as needed
    //        case SDL_WINDOWEVENT:
    //            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
    //                // Update rendering logic or viewport here
    //                int newWidth = event.window.data1;
    //                int newHeight = event.window.data2;
    //                printf("Window resized to %dx%d\n", newWidth, newHeight);

    //                SDL_RenderSetViewport(renderer, NULL);
    //                SDL_RenderSetLogicalSize(renderer, newWidth, newHeight);
    //            }
    //            break;
    //        }
    //    }

    //    backgroundRendering(windowWidth, windowHeight, renderer);

    //    // Render your 2D grid here
    //        // Set of rectangles representing the grid
    //        // Set spacing and width/height to be proportional to window size


    //    // Present the rendered frame
    //    //SDL_RenderPresent(renderer);
    //}

    //// Clean up
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //SDL_Quit();

    GameOfLife theGame;

    theGame.gameStart();

    return 0;
}