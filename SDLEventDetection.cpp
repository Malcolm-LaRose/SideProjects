#include <SDL.h>
#include <stdio.h>

void quitSDL(SDL_Renderer* rend, SDL_Window* wind) {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();

    exit(0);
}



int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Mouse Motion Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 3840, 2160, SDL_WINDOW_FULLSCREEN);
    SDL_HideWindow(window);
    SDL_SetWindowOpacity(window, 0.25f);

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

        SDL_Event test_event;
        while (SDL_PollEvent(&test_event)) {

            auto& pressedKey = test_event.key.keysym.sym;

            if (test_event.type == SDL_QUIT) {
                quit = true;
                break;
            }

            if (test_event.type == SDL_MOUSEMOTION) {
                printf("Current mouse position is: (%d, %d)\n", test_event.motion.x, test_event.motion.y);
                break;
            }
            if (test_event.type == SDL_KEYDOWN && test_event.key.repeat == 0) {
                printf("This key was pressed: %c\n", *SDL_GetKeyName(pressedKey));
                // Compare pressed key to appropriate key in displayed strategem
                if (pressedKey == SDLK_DELETE) {
                    printf("Quitting...\n");
                    quit = true;
                    quitSDL(renderer, window);
                    break;
                }
            }
            else {
                // Do nothing
                // printf("Unhandled Event!\n");
            }

        }
    }

    return 0;
}