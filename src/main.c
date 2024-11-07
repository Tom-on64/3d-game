#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "defs.h"

/* Object */
#define POINT_COUNT 8
#define EDGE_COUNT  12

vec3_t points[POINT_COUNT] = { 
    vec3(-1, -1, -1), 
    vec3(-1, -1, 1),
    vec3(-1, 1, -1), 
    vec3(-1, 1, 1),
    vec3(1, -1, -1), 
    vec3(1, -1, 1),
    vec3(1, 1, -1), 
    vec3(1, 1, 1),
};
vec2_t edges[EDGE_COUNT] = {
    vec2(0, 1),
    vec2(0, 2),
    vec2(0, 4),
    vec2(1, 5),
    vec2(1, 3),
    vec2(2, 3),
    vec2(2, 6),
    vec2(3, 7),
    vec2(4, 5),
    vec2(4, 6),
    vec2(5, 7),
    vec2(6, 7),
};

struct {
    float rot;
    float fov;
    int w;
    int h;
    SDL_Window* window;
    SDL_Renderer* renderer;
} state = { 0 };

void drawFrame(float dt);

int main(void) {
    state.w = 800;
    state.h = 600;
    state.fov = 10.0;

    state.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, state.w, state.h, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);

    int quit = 0;
    long oldtime = SDL_GetTicks();

    while (!quit) {
        long time = SDL_GetTicks();
        float dt = (time - oldtime)/1000.0;
        oldtime = time;

        drawFrame(dt);
        if (SDL_QuitRequested()) { quit = 1; }
    }

    return 0;
}

vec3_t rotate(vec3_t p, float angx, float angy) {
    vec3_t out1;
    vec3_t out2;

    // X rotation
    float cosx = cos(angx);
    float sinx = sin(angx);
    out1.x = p.x;
    out1.y = cosx * p.y - sinx * p.z;
    out1.z = sinx * p.y + cosx * p.z;

    // Y rotation
    float cosy = cos(angy);
    float siny = sin(angy);
    out2.x = cosy * out1.x - siny * out1.z;
    out2.y = out1.y;
    out2.z = siny * out1.x + cosy * out1.z;

    return out2;
}

vec2_t project(vec3_t p) {
    return vec2(
        state.w / 2 + (state.fov * p.x) / (state.fov + p.z) * 100,
        state.h / 2 + (state.fov * p.y) / (state.fov + p.z) * 100
    );
}

void drawFrame(float dt) {
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    state.rot += dt;

    for (int i = 0; i < EDGE_COUNT; i++) {
        vec3_t start = points[(int)edges[i].x];
        vec3_t end = points[(int)edges[i].y];

        // Rotate points
        vec3_t rotStart = rotate(start, state.rot, state.rot);
        vec3_t rotEnd = rotate(end, state.rot, state.rot);
        
        // Project
        vec2_t startp = project(rotStart);
        vec2_t endp = project(rotEnd);
        SDL_RenderDrawLine(state.renderer, startp.x, startp.y, endp.x, endp.y);
    }
    SDL_RenderPresent(state.renderer);
}

