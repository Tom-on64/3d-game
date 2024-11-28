#include <SDL2/SDL.h>
#include "screen.h"
#include "engine.h"

#define FRAMERATE   (60/1000.0f)

screen_t* screen;

int main(void) {
    screen_t s_screen = initScreen("Test Game", 640, 480);
    screen = &s_screen;

    int quit = 0;
    float dt = 0.0f;
    uint32_t lastt = SDL_GetTicks();
    float timer = 0.0f;
    while (!quit) {
        // Check for QUIT event
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = 1; 
        }

        // Calculate deltatime
        uint32_t t = SDL_GetTicks();
        dt = (t - lastt) / 1000.0f;
        lastt = t;

        // Call render and update loops
        update(dt);

        timer += dt;
        if (timer >= FRAMERATE) {
            timer = 0;
            render();
        }

        SDL_Delay(16); // Make sure we don't overload the CPU
    }

    destroyScreen(screen);

    return 0;
}
