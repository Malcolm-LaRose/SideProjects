#include <SDL.h>
#include <SDL_syswm.h>
#include <vector>
#include <stdexcept>



class Grid {
public:
    // Constructor
    Grid(int rows, int cols, std::vector<std::vector<int>>& gridData) : rows(rows), cols(cols), gridData(gridData)
    {
        // Validate grid data dimensions
        if (static_cast<int>(gridData.size()) != rows) {
            throw std::invalid_argument("Invalid number of rows in grid data");
        }
        for (const auto& row : gridData) {
            if (static_cast<int>(row.size()) != cols) {
                throw std::invalid_argument("Invalid number of columns in grid data");
            }
        }
    }

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }

    const std::vector<std::vector<int>>& getGridData() const {
        return gridData; // Returns a reference to the grid data
    }

    int getGridValueAt(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return gridData[row][col];
    }



private:
    int rows;
    int cols;

    std::vector<std::vector<int>> gridData;


};



class Cell {
public:

    // Default constructor
    Cell() : x(0), y(0), size(0), state(false), color( { 0, 0, 0, 255 } ) {}

    // Constructor
    Cell(int x, int y, int size, bool state, std::vector<int> color) : x(x), y(y), size(size), state(state), color(color) {}


    int getXPos() {
        return x;
    }
    int getYPos() {
        return y;
    }
    int getSize() {
        return size;
    }


private:
    int x, y; // Position
    int size; // Square cell has same height and width
    std::vector<int> color;
    bool state; // True = on, false = off

};

class SDLWindowSetup {
public:

    // Constructor
    SDLWindowSetup(const int cellSize, const int cellSpacing, const int screenWidth, const int screenHeight, const int cellX, const int cellY) :
    cellSize(cellSize), cellSpacing(cellSpacing), screenWidth(screenWidth), screenHeight(screenHeight), cellNumberX(cellX), cellNumberY(cellY) {
        calculateWindowHeight();
        calculateWindowHeight();
        centerX = (screenWidth - windowWidth) / 2;
        centerY = (screenHeight - windowHeight) / 2;

    }

    void calculateWindowWidth() {
        windowWidth = 1; // Some calculation (borderWidth*2)+(cellSize*numCells)+(cellSpacing*(numCells - 1)
    }
    void calculateWindowHeight() {
        windowHeight = 1;
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


private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const int screenWidth;
    const int screenHeight;

    int windowWidth;
    int windowHeight;
    int centerX;
    int centerY;
    const int cellSize; // Square cells have same height and width
    const int cellSpacing; 
    const int cellNumberX; // Number of cells in X direction
    const int cellNumberY; // Number of cells in Y direction

    Cell cell;

// Should be able to pass continued rendering off to its own class now
};


class SDLEventHandling {
public:


private:

};

