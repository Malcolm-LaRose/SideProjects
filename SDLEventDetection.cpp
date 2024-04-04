#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Mouse Motion Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    while (!quit) {
        bool validEventDetected = false;
        bool waitingForKeyUp = false;
        while (!validEventDetected) {
            SDL_Event test_event;
            if (!waitingForKeyUp) {
                while (SDL_PollEvent(&test_event)) {
                    auto& pressedKey = test_event.key.keysym.sym;
                    switch (test_event.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_MOUSEMOTION:
                        validEventDetected = true;
                        printf("Current mouse position is: (%d, %d)\n", test_event.motion.x, test_event.motion.y);
                        break;
                    case SDL_KEYDOWN:
                        validEventDetected = true;
                        printf("This key was pressed: %c \n", *SDL_GetKeyName(pressedKey));
                        waitingForKeyUp = true;
                        break;
                    default:
                        printf("Unhandled Event!\n");
                        break;
                    }
                }
            }
            else {
                if (SDL_WaitEvent(&test_event) && test_event.type == SDL_KEYUP) {
                    waitingForKeyUp = false; // Reset the flag when key is released
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}