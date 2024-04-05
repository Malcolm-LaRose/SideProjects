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
        SDL_SetWindowOpacity(c_window, 0.1f);

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

    void clearRenderer() {}

    void drawRenderer() {}

    void showRenderer() {}



    void updateRenderer() {
        // Clear renderer

        // Perform all render functions (draw calls)

        // Show drawings
    }


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
            if (c_event.type == SDL_MOUSEBUTTONDOWN) {
                if (c_event.button.button == SDL_BUTTON_LEFT) {
                    printf("Left click!\n");
                }
                if (c_event.button.button == SDL_BUTTON_RIGHT) {
                    printf("Right click!\n");
                }
            }
            if (c_event.type == SDL_KEYDOWN && c_event.key.repeat == 0) {
                // printf("This key was pressed: %c\n", *SDL_GetKeyName(pressedKey));
                // Compare pressed key to appropriate key in displayed strategem
                if (pressedKey == SDLK_DELETE) {
                    printf("Quitting...\n");
                    quitSDL(c_renderer, c_window);
                    break;
                }
                if (isWASDKey(pressedKey) || isArrowKey(pressedKey)) {
                    // Do something with these keys!
                    // printf("This key was pressed: %c\n", *SDL_GetKeyName(pressedKey));

                    // Here, call a function to draw an arrow corresponding to the 'direction' of the key pressed (this is a placeholder!)
                    if (isUpKey(pressedKey)) {
                        printf("Up!\n");
                    }
                    else if (isLeftKey(pressedKey)) {
                        printf("Left!\n");
                    }
                    else if (isDownKey(pressedKey)) {
                        printf("Down!\n");
                    }
                    else if (isRightKey(pressedKey)) {
                        printf("Right!\n");
                    }
                    
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

    enum WASDKeys {
        Key_W = SDLK_w,
        Key_A = SDLK_a,
        Key_S = SDLK_s,
        Key_D = SDLK_d
    };

    enum ArrowKeys {
        Key_Up = SDLK_UP,
        Key_Left = SDLK_LEFT,
        Key_Down = SDLK_DOWN,
        Key_Right = SDLK_RIGHT
    };

    bool isWASDKey(int key) const {
        return key == Key_W || key == Key_A || key == Key_S || key == Key_D;
    }

    bool isArrowKey(int key) const {
        return key == Key_Up || key == Key_Left || key == Key_Down || key == Key_Right;
    }

    bool isUpKey(int key) const {
        return key == Key_W || key == Key_Up;
    }

    bool isLeftKey(int key) const {
        return key == Key_A || key == Key_Left;
    }

    bool isDownKey(int key) const {
        return key == Key_S || key == Key_Down;
    }

    bool isRightKey(int key) const {
        return key == Key_D || key == Key_Right;
    }
};



int main(int argc, char* argv[]) {

    SDL_Handling sdl;

    bool quit = false;
    while (!quit) {
        
        sdl.handleEvent();
            
    }

    return 0;
}