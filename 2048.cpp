#include "Shapes.h"
#include "Color.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include <cstdio>
#include <memory>
#include <chrono>
#include <random>
#include <optional>
#include <map>
// #include <cmath>

// OPENGL NOT ENABLED IN THIS VERSION | C++17 REQUIRED

// TO DO
	// make cells aware of their col and row
	// Score
	// Game
	// Improve graphics


std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<> randomRowOrCol(0, 3); // Forced to be safe by restricting range here


struct MySettings {

	static MySettings& getInstance() {
		static MySettings instance;
		return instance; // Returns a static reference to the MySettings struct
	}

	const int TARGET_FPS = 180;

	const int INITIAL_SCREEN_WIDTH = 1920; // Initial screen width, can be overriden if necessary (second MySDL_Renderer constructor)
	const int INITIAL_SCREEN_HEIGHT = 1080;

	const int windowMaxWidth = 1920;
	const int windowMaxHeight = 1080;

	const int gridRows = 4;
	const int gridCols = 4;

	const int gridCellSize = 192;
	const int gridCellSpacing = 16;

	// Calculate total width and height of the grid
	int totalWidth = gridCols * gridCellSize + (gridCols + 1) * gridCellSpacing;
	int totalHeight = gridRows * gridCellSize + (gridRows + 1) * gridCellSpacing;

	int& windowMinWidth = totalWidth;
	int& windowMinHeight = totalHeight;

	SDL_Color farBackColor = { 80, 80, 80, 100 };
	SDL_Color backgroundColor = { 204, 192, 178, 255 };
	SDL_Color gridColor = { 187, 173, 160, 255 };


	SDL_Color cell2Color = {233, 228, 218, 255};
	SDL_Color cell4Color = {236,224,202,255};
	SDL_Color cell8Color = {242,177,121,255};
	SDL_Color cell16Color = {236,141,83,255};
	SDL_Color cell32Color = {245,124,95,255};
	SDL_Color cell64Color = {233,89,54,255};
	SDL_Color cell128Color = {244,216,109};
	SDL_Color cell256Color = {241,208,75,255};
	SDL_Color cell512Color = {228,192,42,255};
	SDL_Color cell1024Color = {237, 197,63,255};
	SDL_Color cell2048Color = {236, 196, 5, 255};
	SDL_Color cell4096Color = {60,58,50,255};
	SDL_Color cell8192Color = {30, 29,25,255};



	SDL_Color scoreColor = {};

private:

	MySettings() {} // Don't delete constructor

};

// Put game classes here!

class Cell { // Cells will have to be dynamically created AND DESTROYED! --> Need all constructors
public:
	// Constructors
	Cell(int row, int col) : number(2), row(row), col(col) {}

	Cell(int num, int row, int col) : number(num), row(row), col(col) {}

	// Default destructor is explicitly the default
	~Cell() = default; 

	// Copy constructor --> Should be invoked when a cell is moved from one place to another without merging (copy init)
	Cell(const Cell& other) : number(other.number), row(other.row), col(other.col) {}

	// Copy assignment constructor
	Cell& operator=(const Cell& other) {
		if (this != &other) {
			number = other.number;
			row = other.row;
			col = other.col;
		}
		return *this;
	}

	// Move constructor
	Cell(Cell&& other) noexcept : number(std::move(other.number)), row(std::move(other.row)), col(std::move(other.col)) {}

	// Move assignment operator
	Cell& operator=(Cell&& other) noexcept {
		if (this != &other) {
			number = std::move(other.number);
			row = std::move(other.row);
			col = std::move(other.col);
		}
		return *this;
	}

	int getNumber() {
		return number;
	}

	void updateNumber(int mergingNumber) {
		number = mergingNumber;
	}

	void renderNumber() {
		
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

	void setRow(int newRow) {
		row = newRow;
	}

	void setCol(int newCol) {
		col = newCol;
	}



private:
	int number; // Default 2 for now, add random chance for 4 later
	MySettings& settings = MySettings::getInstance();

	int row;
	int col;



};

class Grid {
public:

	Grid(int cSpace, int cSize) : rows(4), cols(4), cellSpacing(cSpace), cellSize(cSize) {
		gridData.resize(rows, std::vector<std::optional<Cell>>(cols));
		placeRandomCell(); // Start with one cell randomly placed
	}

	bool checkForCellAt(int row, int col) {
		// printf("row: %i col: %i", row, col);
		return (gridData[row][col]).has_value();
	}

	void placeRandomCell() {
		if (isFull()) {
			exit(0);
		}

		int randRow, randCol;
		do {
			randRow = randomRowOrCol(gen);
			randCol = randomRowOrCol(gen);
		} while (checkForCellAt(randRow, randCol));

		Cell cell = createCell(randRow, randCol);
		gridData[randRow][randCol].emplace(cell);
	}

	void moveCellTo(Cell& cell, int newRow, int newCol) {
		int oldRow = cell.getRow();
		int oldCol = cell.getCol();

		// Change the location in gridData
		gridData[newRow][newCol].emplace(cell);
		gridData[oldRow][oldCol].reset();

		// Change the value of row and col stored in the cell --> this should eventually be the only part of this function we need, somehow take care of the rest internally
		cell.setRow(newRow);
		cell.setCol(newCol);

		
	}

	void marchCell(Cell& cell, int rowInc, int colInc) {
		// Move a cell one unit in the grid in the direction specified by rowInc and colInc

		// Get current cell position
		int cellRow = cell.getRow();
		int cellCol = cell.getCol();

		int newRow = cellRow + rowInc;
		int newCol = cellCol + colInc;

		if ((rowInc == 0) && (colInc == 0)) {
			// Do nothing, no move requested
			return;
		}
		else if ((rowInc != 0) && (colInc == 0)) {
			// Invalid move, can't move diagonally --> Should eventually throw an exception here
			return;
		}
		else {
			moveCellTo(cell, newRow, newCol);
		}
		
	}

	void mergeCells(Cell& targetCell, Cell& movingCell) {


		if (targetCell.getNumber() == movingCell.getNumber()) {
			// Merge the cells by updating the value of the first cell
			targetCell.updateNumber((movingCell.getNumber()) * 2);
			// Delete the second cell
			deleteCellAt(movingCell.getRow(), movingCell.getCol());
		}
		
	}

	void deleteCellAt(int row, int col) {
		gridData[row][col].reset();
	}

	void clearGrid() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				deleteCellAt(i, j);
			}
		}
	}

	void moveAndMergeLeft() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) { // Loop through all cells
				
				if (checkForCellAt(i, j)) { // If there is a cell to move

					Cell& movingCell = getCellAt(i, j);

					// Check cells to the left for possible merging
					for (int k = j - 1; k >= 0; k--) {
						if (checkForCellAt(i, k)) { // If there is a cell to the left
							Cell& targetCell = getCellAt(i, k); // Get the cell to the left
							mergeCells(targetCell, movingCell); // Attempt to merge the cells
							break; // Break the loop after attempting to merge
						}
						else {
							// If there is no cell to the left, move the current cell
							moveCellTo(movingCell, i, k);
						}
					}


				}

			}
		}
	}

	//void moveAndMergeAllCells(int rowInc, int colInc) {
	//	// Move cell if able
	//	// Merge if able
	//	// Dont move else

	//	// Move all cells in the direction specified by rowInc and colInc
	//	// Starting point also specified by rI and cI --> if move left, start from left col, if move down start from bottom row, etc...
	//		// Left = 0,0; Bottom = rows,0; Right = 0,cols; Top = 0,cols --> Can be simplified later by starting from 0,0 and rows,cols

	//	for (int i = abs((rows - 1) * rowInc); i < rows; i += rowInc) {
	//		
	//		for (int j = abs((cols - 1) * colInc); j < cols; j += colInc) {
	//			
	//			if (getCellAt(i,j).has_value()) { // If there is a cell

	//				if ()
	//			
	//			}

	//		}
	//	}


	// }

	std::vector<std::vector<std::optional<Cell>>> getGridData() {
		return gridData;
	}

	bool isFull() {
		const int capacity = rows * cols; // Total number of cells on the board
		int filledCells = 1; // Counter for filled cells

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (checkForCellAt(i, j)) {
					filledCells++; // Increment the filled cell count
				}
			}
		}

		fflush(stdout);
		printf("%i", filledCells);


		if (filledCells == capacity) {
			printf("Game over, man!");
			return true;
		}
		
		else {
			return false;
		}
}

	Cell& getCellAt(int row, int col) {
		return gridData[row][col].value();
	}

private:
	const int rows;
	const int cols;

	std::vector<std::vector<std::optional<Cell>>> gridData; // Actual data (empty spaces or Cells)

	const int cellSpacing;
	const int cellSize;

	MySettings& settings = MySettings::getInstance();

	std::optional<Cell> getPotentialCellAt(int row, int col) {
		return gridData[row][col];
	}


	Cell createCell(int row, int col) {
		// Later this can be 2 or 4 randomly
		return Cell(2, row, col);
	}



};

class Score {
public:

	Score() : score(0) {}

	void updateScore() {
	// Call me from the mergeCells function
		// Get the value of the new cell and add it to the score

	}

	uint64_t getScore() {
		return score;
	}


private:

	uint64_t score; // Unsigned 64 bit integer (yuge!)



};

class MySDL_Renderer {
public:


	MySDL_Renderer(SDL_Window* window, Grid& grid) : window(window), renderer(nullptr), SCREEN_WIDTH(settings.INITIAL_SCREEN_WIDTH), SCREEN_HEIGHT(settings.INITIAL_SCREEN_HEIGHT), grid(grid) {
		initSDL();
	}

	MySDL_Renderer(SDL_Window* window, const int wid, const int hei, Grid& grid) : window(window), renderer(nullptr), SCREEN_WIDTH(wid), SCREEN_HEIGHT(hei), grid(grid) {
		initSDL();
	}



	// Disable copy constructor and copy assignment
	MySDL_Renderer(const MySDL_Renderer&) = delete;

	// Disable move constructor and move assignment
	MySDL_Renderer(MySDL_Renderer&&) = delete;

	~MySDL_Renderer()
	{
		quitSDL(); // Last thing in the chain should quit
	}

	SDL_Window* getWindow() {
		return window;
	}

	void quitSDL() {
		if (renderer != nullptr) {
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
			
		}
		if (window != nullptr) {
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		SDL_Quit();
	};


	SDL_Renderer* getRenderer() {
		return renderer;
	}

	int getScWidth() {
		return SCREEN_WIDTH;
	}

	int getScHeight() {
		return SCREEN_HEIGHT;
	}

	void renderAll() {

		adjustScreen();
	
		renderBG();
		renderGrid();
		renderCell();


		presentRender();
		SDL_RenderClear(renderer);
	
	}

private:
	MySettings& settings = MySettings::getInstance();
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


	Grid& grid;


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
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			if (window == nullptr)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetWindowMaximumSize(window, settings.windowMaxWidth, settings.windowMaxHeight);
				SDL_SetWindowMinimumSize(window, settings.windowMinWidth, settings.windowMinHeight);

				// Create renderer for window
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == nullptr)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}


			}
		}

		if (!success)
		{
			quitSDL();
		}

		return success;
	}

	void adjustScreen() {
		SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	}

	void renderBG() {
		Shapes::Point screenTopLeft{ 0, 0 };
		Shapes::Rectangle background(screenTopLeft, SCREEN_WIDTH, SCREEN_HEIGHT, true);
		background.setColor(settings.farBackColor);

		background.render(renderer);

	}

	// Define a map to map cell numbers to colors
	std::map<int, SDL_Color> colorMap = {
		{2, settings.cell2Color},
		{4, settings.cell4Color},
		{8, settings.cell8Color},
		// Add more mappings for other numbers...
	};

	// Function to get color based on cell number
	SDL_Color getColorForNumber(int number) {
		// Check if the number exists in the map
		auto it = colorMap.find(number);
		if (it != colorMap.end()) {
			// Return the corresponding color
			return it->second;
		}
		else {
			// Default color if number doesn't exist in map
			exit(1);
		}
	}

	void renderCell() {
		const int& cellSpacing = settings.gridCellSpacing;
		const int& cellSize = settings.gridCellSize;

		const int& rows = settings.gridRows;
		const int& cols = settings.gridCols;

		// Calculate total width and height of the grid
		int totalWidth = cols * cellSize + (cols + 1) * cellSpacing;
		int totalHeight = rows * cellSize + (rows + 1) * cellSpacing;

		int paddingWidth = (SCREEN_WIDTH / 2) - (totalWidth / 2);
		int paddingHeight = (SCREEN_HEIGHT / 2) - (totalHeight / 2);

		// Get the position from the cells location in the grid
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid.checkForCellAt(i, j)) {
					
					// Set color for cells
					SDL_Color cellColor = getColorForNumber((grid.getCellAt(i, j)).getNumber());

					int topLeftX = cellSpacing * ( j + 1 ) + cellSize * j;
					int topLeftY = cellSpacing * (i + 1) + cellSize * i;

					SDL_Rect cellRect = { topLeftX,topLeftY,cellSize,cellSize };
					cellRect.x += paddingWidth;
					cellRect.y += paddingHeight;


					SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
					SDL_RenderFillRect(renderer, &cellRect);
				}
			}
		}

	
	
	}

	void renderGrid() {
		const int& cellSpacing = settings.gridCellSpacing;
		const int& cellSize = settings.gridCellSize;

		const int& rows = settings.gridRows;
		const int& cols = settings.gridCols;


		// Set color for grid lines
		SDL_Color gridColor = settings.gridColor;

		int paddingWidth = (SCREEN_WIDTH / 2) - (settings.totalHeight / 2);
		int paddingHeight = (SCREEN_HEIGHT / 2) - (settings.totalHeight / 2);


		SDL_Color bgColor = settings.backgroundColor;

		// Render background rectangle
		SDL_Rect bgRect = { 0, 0, settings.totalWidth, settings.totalHeight };

		bgRect.x += paddingWidth;
		bgRect.y += paddingHeight;

		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderFillRect(renderer, &bgRect);

		// Render vertical grid lines
		for (int col = 0; col < cols + 1 ; col++) {
			int x = (col) * cellSize + col * cellSpacing;
			SDL_Rect gridLineRect = { x, 0, cellSpacing, settings.totalHeight };

			gridLineRect.x += paddingWidth;
			gridLineRect.y += paddingHeight;

			SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
			SDL_RenderFillRect(renderer, &gridLineRect);
		}

		// Render horizontal grid lines
		for (int row = 0; row < rows + 1 ; row++) {
			int y = (row) * cellSize + row * cellSpacing;
			SDL_Rect gridLineRect = { 0, y, settings.totalWidth, cellSpacing };

			gridLineRect.x += paddingWidth;
			gridLineRect.y += paddingHeight;

			SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
			SDL_RenderFillRect(renderer, &gridLineRect);
		}



	}

	void renderScore() {}


	void presentRender() { // Or UpdateWindow?
		// Present the rendered image
		auto startTime = std::chrono::high_resolution_clock::now();
		if (renderer == nullptr) {
			return; // Get out of the function
		}

		SDL_RenderPresent(renderer);


		// Calculate time taken to render this frame
		auto endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> frameTime = endTime - startTime;

		const int& targetFPS = settings.TARGET_FPS; // Get target FPS from settings

		// If frame rendering took less time than desired frame rate, introduce a delay
		if (frameTime.count() < (1000.0 / targetFPS)) {
			SDL_Delay((Uint32)((1000.0 / targetFPS) - frameTime.count()));
		}
	}

protected:
	MySDL_Renderer() = delete; // Delete default constructor


};

class MySDL_EventHandler { // This class is mostly for neater organization, no real logical/semantic purpose here (can hide messy code away from main game logic)
public:
	MySDL_EventHandler(SDL_Window* window, MySDL_Renderer* renderer, Grid& grid) : window(window), event(), renderer(renderer), grid(grid) {

	}

	~MySDL_EventHandler() {}

	void pollEvent() {


		while (SDL_PollEvent(&event) != 0) {

			// Log event type
			// printf("Event type: %d\n", event.type);

			if (event.type == SDL_QUIT) {
				renderer->quitSDL();
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {

				// Get coordinates
				std::pair<int, int> mousePosition = getMousePosition();

				// printf("Mouse position - x: %d, y: %d\n", mousePosition.first, mousePosition.second);

				 grid.placeRandomCell();

			}

			else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					// Move and merge cells up
						// Start at leftmost column top row
						// Loop through columns
						// Loop through column
							// If contains a cell, attempt to move up (don't move past grid bounds)
								// Stop at grid bounds
								// Compare values if next gridspace up contains a value
									// If equal, merge, don't move otherwise

					// grid.placeRandomCell();

					break;
				case SDLK_LEFT:
					// Move and merge cells left
					grid.moveAndMergeLeft();
					// grid.placeRandomCell();

					break;
				case SDLK_DOWN:
					// Move and merge cells down

					// grid.placeRandomCell();

					break;
				case SDLK_RIGHT:
					// Move and merge cells right

					// grid.placeRandomCell();

					break;
				}
			}


		}
	}


private:
	SDL_Window* window; // So events can manipulate the window (render is aware of window, should be okay)
	SDL_Event event;
	MySDL_Renderer* renderer; // So events can tell the renderer to do something

	Grid& grid;


	std::pair<int&, int&> getMousePosition() {
		return { event.motion.x, event.motion.y };
	}

};



class MySDL_Wrapper { // This class should collect objects so they're accessible to both the renderer and evHandler, kapische?
public:

	MySDL_Wrapper() : renderer(nullptr), evHandler(nullptr), quit(false), grid(settings.gridCellSpacing, settings.gridCellSize) {
		renderer = new MySDL_Renderer(nullptr, settings.INITIAL_SCREEN_WIDTH, settings.INITIAL_SCREEN_HEIGHT, grid);
		evHandler = new MySDL_EventHandler(renderer->getWindow(), renderer, grid);
	}

	~MySDL_Wrapper() {
		quit = true;
		delete renderer;
		delete evHandler;
	}


	void start() {
		if (!renderer || !evHandler) {
			printf("Renderer or EventHandler is null!\n");
			return; // Exit early if renderer or event handler is not initialized
		}


		while (!quit) {
			evHandler->pollEvent();

			// Big encapsulating rendering function here

			renderer->renderAll();
			// Check if quit event occurred
			if (SDL_QuitRequested()) {
				stop();
			}

		}
		renderer->quitSDL();
	}

	void stop() {
		quit = true;
	}




private:
	MySDL_Renderer* renderer;
	MySDL_EventHandler* evHandler;
	bool quit;

	MySettings& settings = MySettings::getInstance();

	Grid grid;


};


int main(int argc, char* argv[]) {


	MySDL_Wrapper wrap;
	wrap.start();

	return 0;
}