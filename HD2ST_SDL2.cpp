#include <SDL.h>
#include <stdio.h>


class SDL_Handling {
public:
    // Constructor goes here
    SDL_Handling() : c_window(NULL), c_renderer(NULL) {
        initializeSDL();
    }


    // Init
    void initializeSDL() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL initialization failed: %s\n", SDL_GetError());
            exit(1);
        }

        c_window = SDL_CreateWindow("SDL Mouse Motion Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 3840, 2160, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIDDEN);
        SDL_HideWindow(c_window);
        SDL_SetWindowOpacity(c_window, 0.25f);

        if (!c_window) {
            printf("Failed to create SDL window: %s\n", SDL_GetError());
            SDL_Quit();
            exit(1);
        }

        c_renderer = SDL_CreateRenderer(c_window, -1, SDL_RENDERER_ACCELERATED);

        if (!c_renderer) {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(c_window);
            SDL_Quit();
            exit(1);
        }
    }

    // Quit
    void quitSDL(SDL_Renderer* rend, SDL_Window* wind) {
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();

        exit(0);
    }

    // Method for accessing window
    SDL_Window* getWindow() {
        return c_window;
    }

    // Method for accessing renderer
    SDL_Renderer* getRenderer() {
        return c_renderer;
    }


    // Method(s) for updating window



    // Method(s) for updating renderer



    // Method for handling events
    void handleEvent() {
        while (SDL_PollEvent(&c_event)) {

            auto& pressedKey = c_event.key.keysym.sym;

            if (c_event.type == SDL_QUIT) {
                break;
            }

            if (c_event.type == SDL_MOUSEMOTION) {
                printf("Current mouse position is: (%d, %d)\n", c_event.motion.x, c_event.motion.y);
                break;
            }
            if (c_event.type == SDL_KEYDOWN && c_event.key.repeat == 0) {
                printf("This key was pressed: %c\n", *SDL_GetKeyName(pressedKey));
                // Compare pressed key to appropriate key in displayed strategem
                if (pressedKey == SDLK_DELETE) {
                    printf("Quitting...\n");
                    quitSDL(c_renderer, c_window);
                    break;
                }
                else if (false) {
                    // If a valid key is pressed, push it to a vector? or some such
                }
            }
            else {
                // Do nothing
                // printf("Unhandled Event!\n");
            }
        }
    }

    // Destructor
    ~SDL_Handling()  {
        quitSDL(c_renderer, c_window);
    }

private:
    SDL_Window* c_window;
    SDL_Renderer* c_renderer;
    SDL_Event c_event;

};



int main(int argc, char* argv[]) {

    SDL_Handling sdl;

    bool quit = false;
    while (!quit) {
        
        sdl.handleEvent();
            
    }

    return 0;
}