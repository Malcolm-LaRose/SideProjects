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

	// Custom copy constructor
	Cell(const Cell& other) : state(other.state), cellSize(other.cellSize) {}

	// Move constructor
	Cell(Cell&& other) noexcept
		: state(std::move(other.state)), cellSize(other.cellSize) {
		// After moving the state from 'other', we can leave 'other' in a valid but unspecified state
	}


	// Destructor
	~Cell() {}


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
	Grid(int nRows, int nCols) : rows(nRows), cols(nCols), cellSpacing(0) {
		gridData.resize(rows, std::vector<Cell>(cols)); 
	}

	// We can optionally provide a cell spacing
	Grid(int nRows, int nCols, int cSpace) : rows(nRows), cols(nCols), cellSpacing(cSpace) {
		gridData.resize(rows, std::vector<Cell>(cols));
	}

	// ~Grid() : {}

	 // Disable copy constructor
	Grid(const Grid&) = delete;

	// Disable move constructor
	Grid(Grid&&) = delete;

	bool getCellStateAt(int row, int col) {
		Cell& cell = gridData[row][col];
		return cell.getCellState();
	}

	Cell& getCellAt(int row, int col) { // Trying passing by ref
		Cell& cell = gridData[row][col];
		return cell;
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

	int getCellSpacing() const {
		return cellSpacing;
	}

	std::vector<std::vector<Cell>> getGridData() {
		return gridData;
	}



private:
	const int rows; // Number of rows
	const int cols; // Number of cols
	std::vector<std::vector<Cell>> gridData; // The actual data

	const int cellSpacing; // Default 0

};





class MySDL_Renderer {
public:
	MySDL_Renderer(Grid& grid, SDL_Window* window) : grid(grid), window(window), renderer(nullptr), SCREEN_WIDTH(0), SCREEN_HEIGHT(0) {
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
			// Set window size based on grid size
			const int cellSize = grid.getCellAt(0, 0).getCellSize();
			const int cellSpacing = grid.getCellSpacing();

			SCREEN_WIDTH = (grid.getCols()) * cellSize + ((grid.getCols() - 1) * cellSpacing);
			SCREEN_HEIGHT = (grid.getRows()) * cellSize + ((grid.getRows() - 1) * cellSpacing);

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

	void quitSDL() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	};

	void renderGrid() {
		// Implementation of rendering the grid using SDL

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 1, 1, 1, 255); // Background 
		SDL_RenderClear(renderer);

		const int cellSpacing = grid.getCellSpacing();
		const int cellSize = grid.getCellAt(0, 0).getCellSize();

		// Render each cell in the grid
		for (int row = 0; row < grid.getRows(); row++) {
			for (int col = 0; col < grid.getCols(); col++) {
				// Get the state of the cell
				bool cellState = grid.getCellStateAt(row, col);

				// Determine the color based on the cell state
				SDL_Color color;
				if (cellState) {
					color = Color::getSDLColor(Color::PHSORNG); // Phosphor orange for alive cells
				}
				else {
					color = Color::getSDLColor(Color::DRKGRY); // Dark grey for dead cells
				}

				// Calculate the position and size of the cell with spacing
				int x = col * (cellSize + cellSpacing);
				int y = row * (cellSize + cellSpacing);
				SDL_Rect cellRect = { x, y, cellSize, cellSize };

				// Render the cell
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
				SDL_RenderFillRect(renderer, &cellRect);
			}
		}
	}

	void presentRender() {
		// Present the rendered image
		SDL_RenderPresent(renderer);
	}



private:
	Grid& grid;
	SDL_Window* window;
	SDL_Renderer* renderer;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


};


class MySDL_EventHandler { // This class is mostly for neater organization, no real logical/semantic purpose here (can hide messy code away from main game logic)
public:
	MySDL_EventHandler(SDL_Window* window, Grid& grid) : window(window), grid(grid), event() {}

	~MySDL_EventHandler() {}

	void pollEvent() {
		while (SDL_PollEvent(&event) != 0) {
			// If user quits the window, set quit flag to true
			if (event.type == SDL_QUIT) {
				exit(0);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				// Get cell parameters
				const int cellSize = grid.getCellAt(0, 0).getCellSize();
				const int cellSpacing = grid.getCellSpacing();

				// Get coordinates
				int mouseX = 0;
				int mouseY = 0;
				// Convert coordinates to grid location
				int col = (mouseX / (cellSize + cellSpacing));
				int row = (mouseY / (cellSize + cellSpacing));

				// Change clicked cell state
			}
		}
	}

private:
	SDL_Window* window; // So events can manipulate the window (render is aware of window, should be okay)
	Grid& grid; // So this class can do logic involving grid/cell parameters
	SDL_Event event;



};


class GameOfLife {
public:
	// Constructing GoL creates a 100x100 grid of cells
	GameOfLife() // Default GoL will be 100x100 cells and have 2px spaces between cells
		: renderer(nullptr), evHandler(nullptr), grid(100, 100, 2) {
		renderer = new MySDL_Renderer(grid, nullptr); // Initialize the renderer
		evHandler = new MySDL_EventHandler(nullptr, grid); // Set up event handling (so we can use its class functions)
	} 

	// Destructor
	~GameOfLife() {
		delete renderer;
		delete evHandler;
	}

	// Disable copy constructor
	GameOfLife(const GameOfLife&) = delete;

	// Disable move constructor
	GameOfLife(GameOfLife&&) = delete;

	// Logic functions


	// Check neighbors
		// Check cells in all 8 directions around the chosen cell --> edges count as off
		// Push states to a vector
		// Count number true
		// A neat test would be changing the state of the 8 cells surrounding a cell clicked


	// Utility Functions
		


	void sleep() {
		// The time between iterations (for testing, this should be forever)

	}

	void start() {
		// Game loop
		while (!quit) {
			evHandler->pollEvent();
			// updateGrid(); --> Might happen inside of event handling
			renderer->renderGrid(); // This can be combined with the following step into one function if desired
			renderer->presentRender();
			// sleep();
		}
		renderer->quitSDL();
	}

	void stop() {
		quit = true;
	}


private:
	Grid grid;
	MySDL_Renderer* renderer;
	MySDL_EventHandler* evHandler;
	bool quit = false;

};


int main(int argc, char* args[]) {
	GameOfLife game;
	game.start();
	return 0;
}