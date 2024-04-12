// Cell class
	// Can be on or off (true or false)
	// Has a size (square cells)
	// On-ness or off-ness corresponds to a color vector
	// Off should be neutral dark grey
	// On should be phosphor green, orange, or yellow

// Grid class
	// A grid consists of a static 2d array of cells (spacing optional)
	// It has a static number of rows and columns
	// Each grid position contains a cell object that can either be on or off (true or false)

// SDL Rendering class
	// Class to render the grid of cells contained in grid class
	// Just for presentation, no game logic here
	// Need window logic (initializing size based on number of cells and other factors)
	// Include event handling here or elsewhere?
	// Should I break down this class further? What other SDL based classes could I construct that might help me

// SDL Event Handler
	// Polls for events
	// Passes events to game of life for logic

// Game of Life class
	// Has a Grid object initialized full of cells
	// Logic for updating cells based on game of life rules
	// Start with initial layout and update once per second or something
		// Update entire grid at once
	// Easier to start with provided simple layout (glider or something)
	// Later make it pausable and updateable with clicking --> Much later
	// 
	// Passes game state (grid) to the renderer to update visualization

// Questions: Answered
	// Do I want the cells to know their positions in the grid or do I want them to be position agnositc? --> Position agnostic
	// In essence, will I be doing game of life logic on the cells or the grid? --> affects whether game logic is in cell or grid --> game of life

// For now, don't worry about resizing the window --> Force it to a certain size based on grid size and cell size

// SDL include statements
#include <SDL.h>
#include <SDL_syswm.h>

// My include statements
#include "color.h"

// STD include statements
#include <vector>


// Note: Cells should never be 'raw', they should only be instantiated inside of a Grid
class Cell {
public:
	// A cell initialized without a state should be off (false) (default)
	Cell() : state(false), cellSize(10) {}

	// We are allowed to initialize a cell as on if we so choose (or off) (may be useless)
	Cell(bool st) : state(st), cellSize(10) {}

	// ~Cell() : {} // Destructor method


	void updateCellState(bool st) {
		// Update a cell's state
		state = st;
	}

	bool getCellState() {
		return state;
	}

	int getCellSize() { // Sort've redundant, might be better placed in Grid in the future
		return cellSize;
	}

private:
	bool state; // on = true, off = false
	const int cellSize; // Square cell has equal side lengths

};


class Grid {
public:
	// We initialize a vector with a number of rows and cols, each position of which gets a Cell which is default constructed
	Grid(int nRows, int nCols) : rows(nRows), cols(nCols) {
		gridData.resize(rows, std::vector<Cell>(cols)); 
	}

	// ~Grid() : {}

	bool getCellStateAt(int row, int col) {
		Cell& cell = gridData[row][col];
		return cell.getCellState();
	}

	Cell getCellAt(int row, int col) {
		return gridData[row][col];
	}

	void updateCellStateAt(int row, int col, bool newState) { // Want to make an = operator?
		gridData[row][col].updateCellState(newState);
	}

	void resetGrid() { // Sets every cells state to false
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				updateCellStateAt(row, col, false);
			}
		}
	}

	int getRows() const {
		return rows;
	}

	int getCols() const {
		return cols;
	}

	std::vector<std::vector<Cell>> getGridData() {
		return gridData;
	}



private:
	int rows; // Number of rows
	int cols; // Number of cols
	std::vector<std::vector<Cell>> gridData; // The actual data

};





class SDL_Renderer {
public:
	SDL_Renderer(Grid& grid, SDL_Window* window) : grid(grid), window(window), renderer(nullptr), SCREEN_WIDTH(0), SCREEN_HEIGHT(0) {
		initSDL();
	}

	// ~SDL_Renderer() : {}

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
			// Set window size based on grid size
			SCREEN_WIDTH = (grid.getCols()) * (grid.getCellAt(0, 0).getCellSize());
			SCREEN_HEIGHT = (grid.getRows()) * (grid.getCellAt(0, 0).getCellSize());

			// Create window
			window = SDL_CreateWindow("SDL GameOfLife", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

		return success;
	}

	void renderGrid(Grid& grid) {
		// Implementation of rendering the grid using SDL
	}


private:
	Grid& grid;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


};


class SDL_EventHandler {
public:
	SDL_EventHandler(SDL_Window* window, Grid& grid) : window(window), grid(grid) {}

	// ~SDL_EventHandler() : {}

	SDL_Event getEvent() {
		return event;
	}

private:
	SDL_Window* window;
	Grid& grid;
	SDL_Event event;

};


class GameOfLife {
public:
	// Constructing GoL creates a 100x100 grid of cells
	GameOfLife()
		: renderer(nullptr), evHandler(nullptr), grid(100, 100) {}

	// Destructor
	~GameOfLife() {
		delete renderer;
		delete evHandler;
	}


	// Logic functions


	// Check neighbors
		// Check cells in all 8 directions around the chosen cell --> edges count as off
		// Push states to a vector
		// Count number true


	// One Game Step
		// For each cell
			// Count neighbors true
				// GoL

	void start() {
		while (!quit) {
			// handleEvents();
			// updateGrid();
			// renderGrid(); // This can be combined with the following step into one function
			// updateDisplay();
			// sleep();
		}
	}

	void stop() {
		quit = true;
	}

	// Game Loop
		// Loop over game steps
	// while not quit
		// handleEvents, update, render, wait short time (1s), loop


private:
	Grid grid;
	SDL_Renderer* renderer;
	SDL_EventHandler* evHandler;
	bool quit = false;

};


int main(int argc, char* args[]) {
	GameOfLife game;
	game.start();
	return 0;

}