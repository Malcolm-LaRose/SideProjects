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
	int cellSize; // Square cell has equal side lengths

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

	void updateCellStateAt(int row, int col, bool newState) { // Want to make an = operator?
		gridData[row][col].updateCellState(newState);
	}

	void resetGrid() {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				updateCellStateAt(row, col, false);
			}

		}

	}

private:
	int rows; // Number of rows
	int cols; // Number of cols
	std::vector<std::vector<Cell>> gridData; // The actual data

};


class GameOfLife {
public:
	// Constructing GoL creates a 100x100 grid of cells
	GameOfLife() : grid(100, 100) {}

	// ~GameOfLife() : {}

	// Logic functions
	
		// Get cell state at grid location
		// Check neighbors


	// One Game Step
		// For each cell
			// Count neighbors
				// GoL



	// Game Loop


private:
	Grid grid;

};







