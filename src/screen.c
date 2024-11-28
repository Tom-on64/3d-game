#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include "screen.h"

screen_t initScreen(char* title, int width, int height) {
    screen_t screen = {0};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    screen.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!screen.window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    screen.renderer = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);
    if (!screen.renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(screen.window);
        SDL_Quit();
        exit(1);
    }

    screen.texture = SDL_CreateTexture(screen.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!screen.texture) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(screen.renderer);
        SDL_DestroyWindow(screen.window);
        SDL_Quit();
        exit(1);
    }

    screen.pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (!screen.pixels) {
        fprintf(stderr, "Memory allocation failed for screen pixels.\n");
        SDL_DestroyTexture(screen.texture);
        SDL_DestroyRenderer(screen.renderer);
        SDL_DestroyWindow(screen.window);
        SDL_Quit();
        exit(1);
    }

    screen.width = width;
    screen.height = height;

    // Clear the screen to black
    memset(screen.pixels, 0, width * height * sizeof(uint32_t));

    return screen;
}

void destroyScreen(screen_t* screen) {
    if (!screen) return;

    if (screen->pixels) free(screen->pixels);
    if (screen->texture) SDL_DestroyTexture(screen->texture);
    if (screen->renderer) SDL_DestroyRenderer(screen->renderer);
    if (screen->window) SDL_DestroyWindow(screen->window);

    SDL_Quit();
}

void putpixel(screen_t* screen, int x, int y, uint32_t color) {
    if (x < 0 || x >= screen->width || y < 0 || y >= screen->height) return; // Bounds check

    screen->pixels[y * screen->width + x] = color | (0xff >> 24);
}

uint32_t getpixel(screen_t* screen, int x, int y) {
    if (x < 0 || x >= screen->width || y < 0 || y >= screen->height) return 0; // Bounds check

    return screen->pixels[y * screen->width + x];
}

void clearpixels(screen_t* screen, uint32_t color) {
    for (size_t i = screen->width * screen->height; i > 0; i--) {
        screen->pixels[i] = color;
    }
}

int drawframe(screen_t* screen) {
    if (!screen) return -1;

    SDL_UpdateTexture(screen->texture, NULL, screen->pixels, screen->width * sizeof(uint32_t));
    SDL_RenderClear(screen->renderer);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
    SDL_RenderPresent(screen->renderer);

    return 0;
}

