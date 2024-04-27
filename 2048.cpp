#include "Shapes.h"
#include "Color.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include <cstdio>
#include <memory>
#include <chrono>
#include <random>
#include <optional>

// OPENGL NOT ENABLED IN THIS VERSION | C++17 REQUIRED


std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<> randomRowOrCol(0, 3);


struct MySettings {

	static MySettings& getInstance() {
		static MySettings instance;
		return instance; // Returns a static reference to the MySettings struct
	}


	const int INITIAL_SCREEN_WIDTH = 1920; // Initial screen width, can be overriden if necessary (second MySDL_Renderer constructor)
	const int INITIAL_SCREEN_HEIGHT = 1080;

	const int TARGET_FPS = 180;




	const int gridRows = 4;
	const int gridCols = 4;

	const int gridCellSize = 200;
	const int gridCellSpacing = 20;

	const Shapes::Point gameBoardTopLeft{ 40, 40 };

	SDL_Color backgroundColor = { 253, 222, 179, 255 };
	SDL_Color gridColor = {};
	SDL_Color cellColor = {};
	SDL_Color scoreColor = {};

private:

	MySettings() {} // Don't delete constructor

};

// Put game classes here!

class Cell { // Cells will have to be dynamically created AND DESTROYED! --> Need all constructors
public:
	// Constructors
	Cell() : number(2) {}

	Cell(int num) : number(num) {}

	// Default destructor is explicitly the default
	~Cell() = default; 

	// Copy constructor
	Cell(const Cell& other) : number(other.number) {}

	// Copy assignment constructor
	Cell& operator=(const Cell& other) {
		if (this != &other) {
			number = other.number;
		}
		return *this;
	}

	// Move constructor
	Cell(Cell&& other) noexcept : number(std::move(other.number)) {}

	// Move assignment operator
	Cell& operator=(Cell&& other) noexcept {
		if (this != &other) {
			number = std::move(other.number);
		}
		return *this;
	}

	int getNumber() {
		return number;
	}

	void updateNumber(int& mergingNumbers) {
		number = (2 * mergingNumbers);
	}


private:
	int number; // Default 2 for now, add random chance for 4 later


};

class Grid {
public:

	Grid(int cSpace, int cSize) : rows(4), cols(4), cellSpacing(cSpace), cellSize(cSize) {
		gridData.resize(rows, std::vector<std::optional<Cell>>(cols));
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

		Cell cell = createCell();
		gridData[randRow][randCol].emplace(cell);
	}

	void moveCell() {}

	Cell mergeCells(Cell targetCell, Cell movingCell) {
		// Update number of target cell
		int newValue = targetCell.getNumber() + movingCell.getNumber();
		

	}

	void moveAndMergeAllCells() {}

	std::vector<std::vector<std::optional<Cell>>> getGridData() {
		return gridData;
	}

	bool isFull() {
    const int capacity = rows * cols; // Total number of cells on the board
    int filledCells = 0; // Counter for filled cells

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
    } else {
        return false;
    }
}



private:
	const int rows;
	const int cols;

	std::vector<std::vector<std::optional<Cell>>> gridData; // Actual data (empty spaces or Cells)

	const int cellSpacing;
	const int cellSize;

	MySettings& settings = MySettings::getInstance();

	bool checkForCellAt(int row, int col) {
		// printf("row: %i col: %i", row, col);
		return (gridData[row][col]).has_value();
	}

	std::optional<Cell> getCellAt(int row, int col) {
		return gridData[row][col];
	}

	Cell createCell() {
		// Later this can be 2 or 4 randomly
		return Cell(2);
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
	
		renderBG();
		renderGrid();


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
			window = SDL_CreateWindow("SDL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_OPENGL*/);
			if (window == nullptr)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
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

	void renderBG() {
		Shapes::Point screenTopLeft{ 0, 0 };
		Shapes::Rectangle background(screenTopLeft, SCREEN_WIDTH, SCREEN_HEIGHT, true);
		background.setColor(settings.backgroundColor);

		background.render(renderer);

	}

	void renderCell() {}

	void renderGrid() {
		const int& cellSpacing = settings.gridCellSpacing;
		const int& cellSize = settings.gridCellSize;

		const int& rows = settings.gridRows;
		const int& cols = settings.gridCols;

		// Set color for grid lines
		SDL_Color gridColor = Color::getSDLColor(Color::BLACK);

		// Calculate total width and height of the grid
		int totalWidth = cols * cellSize + (cols + 1) * cellSpacing;
		int totalHeight = rows * cellSize + (rows + 1) * cellSpacing;


		SDL_Color bgColor = Color::getSDLColor(Color::WHITE);

		// Render background rectangle
		SDL_Rect bgRect = { 0, 0, totalWidth, totalHeight };
		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderFillRect(renderer, &bgRect);

		// Render vertical grid lines
		for (int col = 0; col < cols + 1 ; col++) {
			int x = (col) * cellSize + col * cellSpacing;
			SDL_Rect gridLineRect = { x, 0, cellSpacing, totalHeight };
			SDL_SetRenderDrawColor(renderer, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
			SDL_RenderFillRect(renderer, &gridLineRect);
		}

		// Render horizontal grid lines
		for (int row = 0; row < rows + 1 ; row++) {
			int y = (row) * cellSize + row * cellSpacing;
			SDL_Rect gridLineRect = { 0, y, totalWidth, cellSpacing };
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

					break;
				case SDLK_LEFT:

					break;
				case SDLK_DOWN:

					break;
				case SDLK_RIGHT:

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