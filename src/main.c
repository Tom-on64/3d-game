#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "engine.h"
#include "render.h"
#include "input.h"
#include "defs.h"

#define DEFAULT_FOV 10.0

// Define vertices and edges for a simple cube
vec3_t cubeVertices[] = { 
    vec3(-1, -1, -1), vec3(-1, -1, 1), vec3(-1, 1, -1), vec3(-1, 1, 1),
    vec3(1, -1, -1), vec3(1, -1, 1), vec3(1, 1, -1),  vec3(1, 1, 1),
};
vec2_t cubeEdges[] = {
    vec2(0, 1), vec2(0, 2), vec2(0, 4), vec2(1, 5), 
    vec2(1, 3), vec2(2, 3), vec2(2, 6), vec2(3, 7), 
    vec2(4, 5), vec2(4, 6), vec2(5, 7), vec2(6, 7),
};
mesh_t cubeMesh = { cubeVertices, cubeEdges, 8, 12 };

// Test object
gameobj_t cube = { 
    vec3(0, 0, 3),  // Position
    vec3(0, 0, 0),  // Rotation
    vec3(1, 1, 1),  // Scale
    &cubeMesh,      // Mesh
};

engineState_t state;

int main(void) {
    state.w = 800;
    state.h = 600;

    // SDL setup
    state.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, state.w, state.h, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED);
    
    // Camera
    state.camera = (camera_t) {
        .position = vec3(0, 0, 0),
        .rotation = vec3(0, 0, 0),
        .fov = DEFAULT_FOV,
        .nearClip = 0.1,
        .farClip = 1000.0,
    };

    int quit = 0;
    long oldtime = SDL_GetTicks();

    while (!quit) {
        long time = SDL_GetTicks();
        float dt = (time - oldtime) / 1000.0;
        oldtime = time;

        drawFrame();
        handleInput(dt);

        if (SDL_QuitRequested()) { quit = 1; }
    }

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();

    return 0;
}

