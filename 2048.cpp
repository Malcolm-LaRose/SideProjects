#include "Shapes.h"
#include "Color.h"

#include <SDL.h>
// #include <SDL_syswm.h> --> Maybe not important?
#include <SDL_ttf.h> // Can't tell if working?

#include <cstdio>
#include <memory>
#include <chrono>
#include <random>
#include <optional>
#include <map>

// OPENGL NOT ENABLED IN THIS VERSION | C++17 REQUIRED

// TO DO
	// Score
	// Improve graphics --> Align numbers and render score
	// Statically link to share with friends


std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<> randomRowOrCol(0, 3); // Forced to be safe by restricting range here
std::uniform_real_distribution<double> random2or4(0.0, 1.0);


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

	SDL_Color farBackColor = { 76, 76, 76, 100 };
	SDL_Color backgroundColor = { 202, 190, 176, 255 };
	SDL_Color gridColor = { 175, 161, 148, 255 };


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
	SDL_Color cell4096Color = {60,116,50,255};
	SDL_Color cell8192Color = {30, 29,25,255};

	SDL_Color numberColor = { 245,245,250,255 };

	SDL_Color scoreColor = {};

private:

	MySettings() {} // Don't delete constructor

};

// Put game classes here!

class Score {
public:

	Score() : score(0) {}
	
	Score(int num) : score(num) {} // Start with the value of the first cell

	void updateScore(int num) {
		// Call me from the mergeCells function
			// Get the value of the new cell and add it to the score
		score += num;
	}

	int getScore() {
		return score;
	}

	void logScore() {
		system("cls");
		printf("Score: %i\n", score);
	}


private:

	int score;



};

class Cell { // Cells will have to be dynamically created AND DESTROYED! --> Need all constructors
public:
	// Constructors
	Cell(int row, int col) : number(2), row(row), col(col), justMerged(false) {}

	Cell(int num, int row, int col) : number(num), row(row), col(col), justMerged(false) {}

	// Default destructor is explicitly the default
	~Cell() = default; 

	// Copy constructor --> Should be invoked when a cell is moved from one place to another without merging (copy init)
	Cell(const Cell& other) : number(other.number), row(other.row), col(other.col), justMerged(other.justMerged) {}

	// Copy assignment constructor
	Cell& operator=(const Cell& other) {
		if (this != &other) {
			number = other.number;
			row = other.row;
			col = other.col;
			justMerged = other.justMerged;

		}
		return *this;
	}

	// Move constructor
	Cell(Cell&& other) noexcept : number(std::move(other.number)), row(std::move(other.row)), col(std::move(other.col)), justMerged(std::move(other.justMerged)) {}

	// Move assignment operator
	Cell& operator=(Cell&& other) noexcept {
		if (this != &other) {
			number = std::move(other.number);
			row = std::move(other.row);
			col = std::move(other.col);
			justMerged = std::move(other.justMerged);
		}
		return *this;
	}

	int getNumber() {
		return number;
	}

	void updateNumber(int mergingNumber) {
		number = mergingNumber;
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

	bool hasMerged() {
		return justMerged;
	}

	void youJustMerged() {
		justMerged = true;
	}

	void resetMerge() {
		justMerged = false;
	}





private:
	int number; // Default 2 for now, add random chance for 4 later
	MySettings& settings = MySettings::getInstance();

	int row;
	int col;

	bool justMerged;



};

class Grid {
public:

	Grid(int cSpace, int cSize) : rows(4), cols(4), cellSpacing(cSpace), cellSize(cSize), score(0) {
		gridData.resize(rows, std::vector<std::optional<Cell>>(cols));
		placeRandomCell(); // Start with one cell randomly placed
		// logGridState();
	}

	void logGridState() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (gridData[i][j].has_value()) {
					// Print the value of the optional cell if it exists
					printf("[%d]", gridData[i][j].value().getNumber());
				}
				else {
					// If cell is empty, print empty brackets
					printf("[]");
				}
				// Add space after each element except the last one in the row
				if (j < cols - 1) {
					printf(" ");
				}
			}
			printf("\n"); // Move to the next row
		}
	}

	bool sameGridState(std::vector<std::vector<std::optional<Cell>>>& before, std::vector<std::vector<std::optional<Cell>>>& after) {
		// Iterate over each cell in the grid
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				// Check if both cells are empty
				if (!before[i][j].has_value() && !after[i][j].has_value()) {
					continue; // Move to the next cell
				}
				// Check if one cell is empty while the other is not
				if (!before[i][j].has_value() || !after[i][j].has_value()) {
					return false;
				}
				// Compare the numbers in non-empty cells
				if (before[i][j].value().getNumber() != after[i][j].value().getNumber()) {
					return false; // Numbers are different
				}
			}
		}

		// All cells are the same
		return true;
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

	void deleteCellAt(int row, int col) {
		gridData[row][col].reset(); // maybe call cell destructor instead?
	}

	void clearGrid() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				deleteCellAt(i, j);
			}
		}
	}

	void moveAndMergeLeft() {

		std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

		for (int i = 0; i < settings.gridRows; i++) {
			for (int j = 1; j < settings.gridCols; j++) { // Start from the second column
				if (checkForCellAt(i, j)) {
					Cell& movingCell = getCellAt(i, j);
					int k = j - 1; // Index of the cell to the left

					// Move the cell as far left as possible
					while (k >= 0 && !checkForCellAt(i, k)) {
						moveCellTo(movingCell, i, k); // Move the cell to the left
						k--; // Move to the next left position
					}

					if (k >= 0 && checkForCellAt(i, k)) {
						Cell& targetCell = getCellAt(i, k);
						mergeCells(targetCell, movingCell);
					}
				}
			}
		}

		resetCellMergeFlag();

		std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

		if (!sameGridState(beforeGrid, afterGrid)) {
			placeRandomCell();
		}

	}

	void moveAndMergeRight() {

		std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

		for (int i = 0; i < rows; i++) {
			for (int j = cols - 1; j >= 0; j--) { // Start from the second-to-last column and move leftwards
				if (checkForCellAt(i, j)) { // If there is a cell to move
					Cell& movingCell = getCellAt(i, j);
					int k = j + 1; // Index of the cell to the right

					// Move the cell as far right as possible
					while (k < cols && !checkForCellAt(i, k)) {
						moveCellTo(movingCell, i, k); // Move the cell to the right
						k++; // Move to the next right position
					}

					if (k < cols && checkForCellAt(i, k)) {
						Cell& targetCell = getCellAt(i, k);
						mergeCells(targetCell, movingCell);
					}
				}
			}
		}

		resetCellMergeFlag();

		std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

		if (!sameGridState(beforeGrid, afterGrid)) {
			placeRandomCell();
		}

	}


	void moveAndMergeUp() {

		std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (checkForCellAt(i, j)) {
					Cell& movingCell = getCellAt(i, j);
					int k = i - 1; // Index of cell up

					// Move the cell as far up as possible
					while (k >= 0 && !checkForCellAt(k, j)) {
						moveCellTo(movingCell, k, j);
						k--;
					}

					if (k >= 0 && checkForCellAt(k, j)) { // Merge if possible
						Cell& targetCell = getCellAt(k, j);
						mergeCells(targetCell, movingCell);
					}
				}
			}
		}

		resetCellMergeFlag();

		std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

		if (!sameGridState(beforeGrid, afterGrid)) {
			placeRandomCell();
		}

	}

	void moveAndMergeDown() {

		std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

		for (int i = rows - 1; i >= 0; i--) {
			for (int j = 0; j < cols; j++) {
				if (checkForCellAt(i, j)) {
					Cell& movingCell = getCellAt(i, j);
					int k = i + 1; // Index of cell down

					// Move the cell as far down as possible
					while (k < rows && !checkForCellAt(k, j)) {
						moveCellTo(movingCell, k, j);
						k++;
					}

					if (k < rows && checkForCellAt(k, j)) { // Merge if possible
						Cell& targetCell = getCellAt(k, j);
						mergeCells(targetCell, movingCell);
					}
				}
			}
		}

		resetCellMergeFlag();

		std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

		if (!sameGridState(beforeGrid, afterGrid)) {
			placeRandomCell();
		}

	}



	std::vector<std::vector<std::optional<Cell>>>& getGridData() {
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
		// printf("%i", filledCells);


		if (filledCells == capacity) {
			printf("Game over, man!");
			system("pause");
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

	Score score;

	std::optional<Cell> getPotentialCellAt(int row, int col) {
		return gridData[row][col];
	}

	void moveCellTo(Cell& cell, int newRow, int newCol) {
		int oldRow = cell.getRow();
		int oldCol = cell.getCol();

		if (oldRow != newRow || oldCol != newCol) { // check for valid moves
			// Change the value of row and col stored in the cell --> this should eventually be the only part of this function we need, somehow take care of the rest internally
			cell.setRow(newRow);
			cell.setCol(newCol); // --> ABSOLUTELY CRITICAL TO DO THIS BEFORE NEXT TWO STATEMENTS

			// Change the location in gridData
			gridData[newRow][newCol].emplace(cell);
			deleteCellAt(oldRow, oldCol);
		}
	}

	void resetCellMergeFlag() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (gridData[i][j].has_value()) {
					gridData[i][j].value().resetMerge();
				}
			}
		}
	}

	void mergeCells(Cell& targetCell, Cell& movingCell) {
		if ((targetCell.getNumber() == movingCell.getNumber()) && (!targetCell.hasMerged())) {
			// Merge the cells by updating the value of the first cell
			targetCell.updateNumber((movingCell.getNumber()) * 2);
			// Update score
			score.updateScore(targetCell.getNumber());
			// Delete the second cell
			deleteCellAt(movingCell.getRow(), movingCell.getCol());
			// Log score to console for now
			score.logScore();
			targetCell.youJustMerged();
			return;
		}

		else return;

	}

	int twoOrFour() {
		double randomNum = random2or4(gen);

		if (randomNum > 0.9) {
			return 4;
		}
		else {
			return 2;
		}

	}

	Cell createCell(int row, int col) {
		// Later this can be 2 or 4 randomly
		return Cell(twoOrFour(), row, col);
	}
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

				// Initialize SDL_ttf
				if (TTF_Init() != 0) {
					printf("SDL_ttf initialization failed");
					SDL_Quit();
					return 1;
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
	{16, settings.cell16Color},
	{32, settings.cell32Color},
	{64, settings.cell64Color},
	{128, settings.cell128Color},
	{256, settings.cell256Color},
	{512, settings.cell512Color},
	{1024, settings.cell1024Color},
	{2048, settings.cell2048Color},
	{4096, settings.cell4096Color},
	{8192, settings.cell8192Color},
	// Add more mappings as needed for higher numbers...
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

	void renderNumber(int num, int xPos, int yPos) {
		// Shapes::Text numberText(num, 100, { 100, 100 });
		// numberText.render(renderer);

		int fontSizeLarge = 100;

		Shapes::Text numToRender(num, fontSizeLarge, { xPos + (settings.gridCellSize / 2), yPos + (settings.gridCellSize / 2) });
		numToRender.render(renderer);

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

					Cell& cell = grid.getCellAt(i,j);
					
					// Set color for cells
					SDL_Color cellColor = getColorForNumber((grid.getCellAt(i, j)).getNumber());

					int topLeftX = cellSpacing * ( j + 1 ) + cellSize * j;
					int topLeftY = cellSpacing * (i + 1) + cellSize * i;

					SDL_Rect cellRect = { topLeftX,topLeftY,cellSize,cellSize };
					cellRect.x += paddingWidth;
					cellRect.y += paddingHeight;


					SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
					SDL_RenderFillRect(renderer, &cellRect);

					// Place text here
					renderNumber(cell.getNumber(),topLeftX+paddingWidth,topLeftY+paddingHeight);


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

			//else if (event.type == SDL_MOUSEBUTTONDOWN) {
			//
			//	// Get coordinates
			//	std::pair<int, int> mousePosition = getMousePosition();
			//
			//	 printf("Mouse position - x: %d, y: %d\n", mousePosition.first, mousePosition.second);
			//
			//	  grid.placeRandomCell();
			//	  grid.logGridState();
			//
			//}

			else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					// Move and merge cells up
					grid.moveAndMergeUp();
					// grid.placeRandomCell();

					break;
				case SDLK_LEFT:
					// Move and merge cells left
					grid.moveAndMergeLeft();
					// grid.logGridState();
					// grid.placeRandomCell();

					break;
				case SDLK_DOWN:
					// Move and merge cells down
					grid.moveAndMergeDown();
					// grid.placeRandomCell();

					break;
				case SDLK_RIGHT:
					// Move and merge cells right
					grid.moveAndMergeRight();
					// grid.logGridState();
					// grid.placeRandomCell();

					break;
				}
			}


		}
	}

	bool playAgain() {}


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