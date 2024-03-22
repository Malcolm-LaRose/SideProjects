#include <SDL.h>
#include <SDL_syswm.h>

class Color {
public:

    // Constructor
    Color(int r, int g, int b, int alpha) : red(r), green(g), blue(b), transparency(alpha) {}
    
    // Allowed colors
    enum NamedColor {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE

    };

    Color getColorFromNamedColor(NamedColor namedColor) {
        switch (namedColor) {
        case WHITE:
            return Color{ 255, 255, 255, 255 };
        case BLACK:
            return Color{ 0, 0, 0, 255 };
        case RED:
            return Color{ 255, 0, 0, 255 };
        case GREEN:
            return Color{ 0, 255, 0, 255 };
        case BLUE:
            return Color{ 0, 0, 255, 255 };
        default:
            // Handle invalid named color
            // You could throw an exception or return a default color
            return { 0, 0, 0, 0 }; // Default to fully transparent black
        }
    }



private:
    int red;
    int green;
    int blue;
    int transparency;


};

class Cell {
public:
    int getXPos() {
        return x;
    }
    int getYPos() {
        return y;
    }


private:
    int x, y; // Position
    int size; // Square cell has same height and width

};

class SDLWindowDisplayandRendering {
public:

    // Constructor
    SDLWindowDisplayandRendering(const int cellSize, const int cellSpacing, const int screenWidth, const int screenHeight, const int cellX, const int cellY) :
    cellSize(cellSize), cellSpacing(cellSpacing), screenWidth(screenWidth), screenHeight(screenHeight), cellNumberX(cellX), cellNumberY(cellY) {
        calculateWindowHeight();
        calculateWindowHeight();
        centerX = (screenWidth - windowWidth) / 2;
        centerY = (screenHeight - windowHeight) / 2;

    }

    void calculateWindowWidth() {
        windowHeight = 1; // Some calculation (borderWidth*2)+(cellSize*numCells)+(cellSpacing*(numCells - 1)
    }
    void calculateWindowHeight() {}


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

};


class SDLEventHandling {
public:


private:


};