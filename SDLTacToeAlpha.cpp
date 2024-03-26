#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// Screen dimension constants (non-const so we can resize)
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

// Initial screen dimension constants
int initialScreenWidth = 500;
int initialScreenHeight = 500;

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
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
                        // Add more event handling as needed
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