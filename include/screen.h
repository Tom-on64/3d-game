#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;
    int width;
    int height;
} screen_t;

screen_t initScreen(char* title, int width, int height);
void destroyScreen(screen_t* screen);

void putpixel(screen_t* screen, int x, int y, uint32_t color);
uint32_t getpixel(screen_t* screen, int x, int y);
void clearpixels(screen_t* screen, uint32_t color);
int drawframe(screen_t* screen);

#endif
