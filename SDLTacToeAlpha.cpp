#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <utility>
#include <stdio.h>

class Player {
public:

    Player(char pName, SDL_Texture* pText) : playerName(pName), playerTexture(pText) {} // Must give players a name and a texture

    char getPlayerName() {
        return playerName;
    }

    SDL_Texture* getPlayerTexture() {
        return playerTexture;
    }

    ~Player() {
        if (playerTexture != nullptr)
        {
            SDL_DestroyTexture(playerTexture);
            playerTexture = nullptr;
        }
    }

private: 
    char playerName;
    SDL_Texture* playerTexture;


};

class TicTacToe {
public:

    // void startGame() {} Maybe replaced with constructor
    // TicTacToe(Player one, Player two) : playerOne(one), playerTwo(two) {}

    void setPlayerOneAndTwo() {
    };




private:
    std::vector<std::vector<char>> boardState;
    Player playerOne;
    Player playerTwo;
    

};// To be worked on later



// Screen dimension constants (non-const so we can resize)
int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;

// Initial screen dimension constants
int initialScreenWidth = 600;
int initialScreenHeight = 600;

// Function prototypes
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(const char* path);
void renderTexture(SDL_Texture* texture, int x, int y, int width, int height);
void updateTexture();


// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The renderer we'll be using
SDL_Renderer* gRenderer = NULL;

// The textures for game objects
SDL_Texture* gBoardTexture = NULL;
SDL_Texture* gPlayerXTexture = NULL;
SDL_Texture* gPlayerOTexture = NULL;
SDL_Texture* gWinLineTexture = NULL;

void updateTexture() {
    return;
}

//void updateTexture() { // PLACEHOLDER IDEA
//    // Example game state for Tic-Tac-Toe
//    // Assume a 3x3 game board represented by a 2D array
//    // '0' represents an empty cell, '1' represents a cell with 'X', '2' represents a cell with 'O'
//    int gameState[3][3] = {
//        {1, 0, 2},
//        {0, 1, 2},
//        {2, 1, 0}
//    };
//
//    // Calculate the dimensions of each cell on the game board
//    int cellWidth = SCREEN_WIDTH / 3;
//    int cellHeight = SCREEN_HEIGHT / 3;
//
//    // Iterate through the game state and render textures for each cell
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            // Calculate the position of the current cell
//            int cellX = j * cellWidth;
//            int cellY = i * cellHeight;
//
//            // Render different textures based on the game state
//            if (gameState[i][j] == 1) {
//                renderTexture(gPlayerXTexture, cellX, cellY, cellWidth, cellHeight);
//            }
//            else if (gameState[i][j] == 2) {
//                renderTexture(gPlayerOTexture, cellX, cellY, cellWidth, cellHeight);
//            }
//            // You can add more conditions based on your game logic
//            // For example, rendering a different texture for an empty cell
//            else {
//                // Render an empty cell texture (if available)
//                // Example: renderTexture(gEmptyCellTexture, cellX, cellY, cellWidth, cellHeight);
//            }
//        }
//    }
//}


SDL_Texture* loadTexture(const char* path)
{
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void renderTexture(SDL_Texture* texture, int x, int y, int width, int height)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };
    SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
}

bool init()
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
        gWindow = SDL_CreateWindow("SDL TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load splash images
    gBoardTexture = loadTexture("Graphics/board.bmp");
    if (gBoardTexture == NULL)
    {
        printf("Failed to load image %s!\n", "Graphics/board.bmp");
        success = false;
    }

    gPlayerXTexture = loadTexture("Graphics/x.bmp");
    if (gPlayerXTexture == NULL)
    {
        printf("Failed to load image %s!\n", "Graphics/x.bmp");
        success = false;
    }

    gPlayerOTexture = loadTexture("Graphics/o.bmp");
    if (gPlayerOTexture == NULL)
    {
        printf("Failed to load image %s!\n", "Graphics/o.bmp");
        success = false;
    }

    gWinLineTexture = loadTexture("Graphics/line.bmp");
    if (gWinLineTexture == NULL)
    {
        printf("Failed to load image %s!\n", "Graphics/line.bmp");
        success = false;
    }

    return success;
}

void close()
{
    // Destroy textures
    SDL_DestroyTexture(gBoardTexture);
    SDL_DestroyTexture(gPlayerXTexture);
    SDL_DestroyTexture(gPlayerOTexture);
    SDL_DestroyTexture(gWinLineTexture);

    // Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


std::pair<int,int> getMousePosition(SDL_Event event) {
    return { event.motion.x, event.motion.y };
}

void detectCellClicked(SDL_Event event) {
    // Should eventually return iterators for accessing game state array
    std::pair<int, int> mousePosition = getMousePosition(event);
    int* xCoord = &mousePosition.first; // No need to make a new copy, lets try using a pointer
    int* yCoord = &mousePosition.second;
    printf("You clicked these coordinates: (%d, %d)\n", *xCoord, *yCoord);

    //if (x coord less than 195) {
    //    if (y coord less than 195) {

    //    }
    //    if (y coord greater than 200 and less than 495) {

    //    }
    //    if (y coord greater than 500) {

    //    }
    //}

    printf("You clicked on cell (%d, %d)\n", 0, 0); // Eventually return a pair of ints
}


int main(int argc, char* args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main Loop Flag
            bool quit = false;

            // Event Handler
            SDL_Event e;

            // Player init
            Player playerX('x', gPlayerXTexture);
            Player playerO('o', gPlayerOTexture);

            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_WINDOWEVENT:
                        // Handle window events
                        switch (e.window.event) {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            // Get new dimensions
                            SCREEN_WIDTH = e.window.data1;
                            SCREEN_HEIGHT = e.window.data2;
                            break;
                            // Add more window event handling as needed
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        // Detect where click occured
                        if (e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT) {
                            // If a click occurs, which cell was clicked?
                            detectCellClicked(e);
                        // put player texture in region detected
                        // if click out of bounds, do nothing
                        // 
                        }

                        // Add more event handling as needed
                        break;
                    }

                }

                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render textures with scaled dimensions
                renderTexture(gBoardTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}