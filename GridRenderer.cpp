#include <SDL.h>
#include <SDL_syswm.h>
#include <vector>
#include <stdexcept>

// Forward class declarations





// Data stuff

class Cell {
public:

    // Default constructor
    Cell() : x(0), y(0), size(0), state(false), color({ 0, 0, 0, 255 }) {}

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

class Grid {
public:
    // Default constructor
    Grid() : rows(20), cols(20) {
        constructGrid();
    }


    // Constructor
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        // Validate grid data dimensions
        if (static_cast<int>(gridData.size()) != rows) {
            throw std::invalid_argument("Invalid number of rows in grid data");
        }
        for (const auto& row : gridData) {
            if (static_cast<int>(row.size()) != cols) {
                throw std::invalid_argument("Invalid number of columns in grid data");
            }
        }

        constructGrid();
    }

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }

    const std::vector<std::vector<Cell>>& getGridData() const {
        return gridData; // Returns a reference to the grid data
    }

    Cell getGridValueAt(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Index out of range");
        }
        return gridData[row][col];
    }

    void constructGrid() { // Make the data grid
        gridData.resize(rows); // Works vertically

        // For each row, resize the vector to have 'cols' columns
        for (int i = 0; i < rows; ++i) { // Works horizontally
            gridData[i].resize(cols);
        }
    }

    void initializeGrid() {
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // Construct an empty cell
            }
        }
    }



private:
    int rows;
    int cols;

    std::vector<std::vector<Cell>> gridData;


};

class Border {
public:
    // Default constructor
    Border() :borderSizePX(6) {}


    int getBorderSize() {
        return borderSizePX;
    }

private:
    int borderSizePX;

};



// Graphics stuff

class SDLWindowSetupAndRun {
public:
    // Default Constructor 
    SDLWindowSetupAndRun() : cellSize(18), cellSpacing(6), screenWidth(3840), screenHeight(2160), borderSize(6) {
    calculateWindowHeight();
        calculateWindowWidth();
        centerX = (screenWidth - windowWidth) / 2;
        centerY = (screenHeight - windowHeight) / 2;
        numRows = grid.getRows();
        numCols = grid.getCols();
        fullInitialization();
    }

    // Constructor
    SDLWindowSetupAndRun(const int cellSize, const int cellSpacing, const int screenWidth, const int screenHeight, const int borderSize) :
    cellSize(cellSize), cellSpacing(cellSpacing), screenWidth(screenWidth), screenHeight(screenHeight), borderSize(borderSize) {
        calculateWindowHeight();
        calculateWindowWidth();
        centerX = (screenWidth - windowWidth) / 2;
        centerY = (screenHeight - windowHeight) / 2;
        numRows = grid.getRows();
        numCols = grid.getCols();
        fullInitialization();
    }

    // Window setup functions

    void calculateWindowWidth() {
        windowWidth = (cellSpacing*2)+(cellSize*numCols)+(borderSize*2); // Gutters + cells + borders = full width
    }
    void calculateWindowHeight() {
        windowHeight = (cellSpacing * 2) + (cellSize * numRows) + (borderSize * 2); // Gutters + cells + borders = full height
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


    // Accessor functions

    SDL_Window* getWindow() {
        return window;
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

    int getWindowWidth() {
        return windowWidth;
    }

    int getWindowHeight() {
        return windowHeight;
    }





private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const int screenWidth;
    const int screenHeight;

    const int borderSize;
    int windowWidth;
    int windowHeight;
    int centerX;
    int centerY;
    const int cellSize; // Square cells have same height and width
    const int cellSpacing; 
    int numRows; // Number of cells in X direction
    int numCols; // Number of cells in Y direction

    Grid grid;

// Should be able to pass continued rendering off to its own class now
};

class SDLRender {
public:






    void calculateBorder() {

    }

    void renderBackground() {

    }

private:


};


class SDLEventHandling {
public:


private:

};


int main(int argc, char* args[]) {

    Grid gameGrid;
    SDLWindowSetupAndRun sdlWindow;

    return 0;
}
