#include <SDL.h>
#include <SDL_syswm.h>
#include <vector>
#include <stdexcept>
#include <iostream>


// Data stuff

class Cell {
public:

    // Default constructor
    Cell() : x(0), y(0), size(0), state(false), color( { 20, 20, 20, 255 } ) {}

    // Lazy constructor


    // Constructor
    Cell(int x, int y, int size, bool state, std::vector<int> color) : x(x), y(y), size(size), state(state), color(color) {}


    int getXPos() { // Pos of upper left corner
        return x;
    }
    int getYPos() { // Pos of upper left corner
        return y;
    }
    int getSize() {
        return size;
    }
    bool getState() {
        return state;
    }
    std::vector<int> getColor() {
        return color;
    }


private:
    int x, y; // Position of upper left corner
    int size; // Square cell has same height and width
    std::vector<int> color;
    bool state; // True = on, false = off

    void changeColor() {
        if (!state) {
            color = { 20, 20, 20, 255 }; // Neutral grey
        }
        else {
            color = { 255, 204, 0, 255 }; // 593nm phosphor orange
        }
    }



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

class Grid {
public:
    // Default constructor
    Grid() : rows(20), cols(20), cellSpacing(6) {
        constructGrid();
    }


    // Constructor
    Grid(int rows, int cols, int cSize, int cSpacing) : rows(rows), cols(cols), cellSpacing(cSpacing) {
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

    std::vector<std::vector<Cell>> getGridData(){
        return gridData; // Returns a reference to the grid data
    }

    Cell getGridCellAt(int row, int col) {
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
        std::cout << "Grid constructed" << std::endl;
    }

    void initializeGrid() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // Construct an empty cell and iterate over coordinates and gridData
                int startingPosX = border.getBorderSize() + j * (cellSpacing + 20); // Calculate starting X position of cell
                int startingPosY = border.getBorderSize() + i * (cellSpacing + 20); // Calculate starting Y position of cell

                // Initialize the cell at current position
                gridData[i][j] = Cell(startingPosX, startingPosY, 20, false, { 20, 20, 20, 255 });

                // Print cell information
                std::cout << "Cell color: " << gridData[i][j].getColor()[0] << ", "
                    << gridData[i][j].getColor()[1] << ", "
                    << gridData[i][j].getColor()[2] << ", "
                    << gridData[i][j].getColor()[3] << std::endl;
                std::cout << "Cell position: (" << i << ", " << j << ")" << std::endl;

                if (j == 19) {
                    break;
                }
            }
            if (i == 19) {
                break;
            }
        }
        std::cout << "Grid init'ed" << std::endl;
    }



    const int getCellSpacing() const {
        return cellSpacing;
    }



private:
    int rows;
    int cols;

    const int cellSpacing;

    std::vector<std::vector<Cell>> gridData;
    Border border;


};




// Graphics stuff
class SDLRender {
public:
    SDLRender(SDL_Window* window, SDL_Renderer* renderer, Grid grid)
        : window(window), renderer(renderer), grid(grid) {}

    void renderGrid() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color (white)

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render cells
        std::vector<std::vector<Cell>> gridData = grid.getGridData();
        for (int i = 0; i < grid.getRows(); ++i) {
            for (int j = 0; j < grid.getCols(); ++j) {
                Cell& cell = gridData[i][j];

                // Debug output to check cell position
                std::cout << "Cell position: (" << j << ", " << i << ")" << std::endl;
                std::cout << "Cell color: " << cell.getColor()[0] << ", " << cell.getColor()[1] << ", " << cell.getColor()[2] << ", " << cell.getColor()[3] << std::endl; // Debug output

                SDL_SetRenderDrawColor(renderer, cell.getColor()[0], cell.getColor()[1], cell.getColor()[2], cell.getColor()[3]);

                int cellX = j * (cell.getSize() + grid.getCellSpacing());
                int cellY = i * (cell.getSize() + grid.getCellSpacing());
                SDL_Rect cellRect = { cellX, cellY, cell.getSize(), cell.getSize() };


                SDL_RenderFillRect(renderer, &cellRect);
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Grid grid;

};

void renderGrid(SDL_Window* window, SDL_Renderer* renderer, Grid grid) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color (white)

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render cells
    std::vector<std::vector<Cell>> gridData = grid.getGridData();
    for (int i = 0; i < grid.getRows(); ++i) {
        for (int j = 0; j < grid.getCols(); ++j) {
            Cell& cell = gridData[i][j];

            // Debug output to check cell position
            std::cout << "Cell position: (" << j << ", " << i << ")" << std::endl;
            std::cout << "Cell color: " << cell.getColor()[0] << ", " << cell.getColor()[1] << ", " << cell.getColor()[2] << ", " << cell.getColor()[3] << std::endl; // Debug output

            SDL_SetRenderDrawColor(renderer, cell.getColor()[0], cell.getColor()[1], cell.getColor()[2], cell.getColor()[3]);

            int cellX = j * (cell.getSize() + grid.getCellSpacing());
            int cellY = i * (cell.getSize() + grid.getCellSpacing());
            SDL_Rect cellRect = { cellX, cellY, cell.getSize(), cell.getSize() };


            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}


int main(int argc, char* args[]) {
    // Create grid
    Grid gameGrid;
    gameGrid.initializeGrid();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("2D Grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Render grid
    renderGrid(window, renderer, gameGrid);

    // Main loop, event handling, etc.
    bool quit = false;
    while (!quit) {
        // Handle events
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { // Check if the user closed the window
                quit = true;
            }
            // Handle other events such as window resizing if necessary
        }

        // Render the grid
        renderGrid(window, renderer, gameGrid);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
