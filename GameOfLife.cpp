#include <SDL.h>
#include <SDL_syswm.h>
#include <list>
#include <vector>

class Cell {
public:
    int x, y; // Position
    int size;

private:


};


class GameOfLife {
public:

    GameOfLife(int initialWidth, int initialHeight, int gridSize) : windowWidth(initialWidth), windowHeight(initialHeight), gridSize(gridSize) {
        centerX = (screenWidth - windowWidth) / 2;
        centerY = (screenHeight - windowHeight) / 2;
        calculateBorder();
        calculateCells();
    }

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

                    windowWidth = newWidth;
                    windowHeight = newHeight;

                    // Recalculate center
                    centerX = (screenWidth - windowWidth) / 2;
                    centerY = (screenHeight - windowHeight) / 2;

                    // Update renderer logical size
                    SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

                    // Recalculate border
                    calculateBorder();
                    calculateCells();

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

        // Set initial logical size
        SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
    }
    void fullInitialization() {
        // DPI awareness
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(SDL_CreateWindow("", 0, 0, 100, 100, SDL_WINDOW_HIDDEN), &wmInfo);
        SetProcessDPIAware(); // Or use SetProcessDpiAwareness() for more control


        // Initialize SDL
        SDL_Init(SDL_INIT_VIDEO);

        initWindow();
        initRenderer();

    }

    // Calculate border rectangle dimensions and position
    void calculateBorder() {
        borderRect.x = borderSize;
        borderRect.y = borderSize;
        borderRect.w = windowWidth - (300 + (2 * borderSize));
        borderRect.h = windowHeight - (2 * borderSize);
    }

    // Calculate cell positions and sizes
    void calculateCells() {
        int gridWidth = borderRect.w - borderSize * (gridSize - 1); // Calculate the width of the grid area (excluding borders between cells)
        cellSize = gridWidth / gridSize; // Calculate cell size based on grid size and width of the grid area
        cells.clear(); // Clear existing cells

        // Calculate positions and sizes of all cells
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                Cell cell;
                cell.x = borderRect.x + j * (cellSize + borderSize); // Add borderSize to account for border between cells
                cell.y = borderRect.y + i * (cellSize + borderSize); // Add borderSize to account for border between cells
                cell.size = cellSize;
                cells.push_back(cell);
            }
        }
    }
    
    void backgroundRender() {
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background black
        SDL_RenderClear(renderer); 

        //int newWidth = windowWidth - 312;
        //int newHeight = windowHeight - 12;

        //// Recalculate the dimensions of the border rectangle
        //SDL_Rect fullBorder = { 6, 6, newWidth, newHeight };

        // Render the border rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Border white
        SDL_RenderDrawRect(renderer, &borderRect);

        // Render cells
        SDL_SetRenderDrawColor(renderer, 0, 255, 51, 255); // Cell walls green
        for (const auto& cell : cells) {
            SDL_Rect cellRect = { cell.x, cell.y, cell.size, cell.size };
            SDL_RenderFillRect(renderer, &cellRect);
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    void gameLoop() {
        // Main loop
        bool isRunning = true;

        // Initialization
        fullInitialization();

        while (isRunning) {
            backgroundRender();
            eventHandler(isRunning);

            }

            // Render your 2D grid here
                // Set of rectangles representing the grid
                // Set spacing and width/height to be proportional to window size


            // Present the rendered frame
            //SDL_RenderPresent(renderer);
        }

    void cleanUp() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


private:
    // SDL Stuff
    SDL_Event event;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Rect borderRect;

    // Important numerical values
    const int screenWidth = 3840;
    const int screenHeight = 2160;
    const int borderSize = 6; //px
    int windowWidth;
    int windowHeight;
    int centerX;
    int centerY;

    int numCellsX;
    int numCellsY;

    // Grid properties
    int gridSize; // Number of cells in one row/column
    int cellSize; // Size of each cell
    std::vector<Cell> cells; // Vector to store cell information


// End of GOL class
};




int main(int argc, char* args[])
{

    int initialWidth = 1920;
    int initialHeight = 1080;

    GameOfLife theGame(initialWidth, initialHeight, 100);

    theGame.gameLoop();
    theGame.cleanUp();

    return 0;
}