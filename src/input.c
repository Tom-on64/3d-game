#include <SDL2/SDL.h>
#include "engine.h"
#include "render.h"
#include "defs.h"

// Speed factors for movement and rotation
static const float moveSpeed = 2.0f;
static const float rotateSpeed = 1.0f;

extern gameobj_t cube;

void handleInput(float dt) {
    const unsigned char* keystate = SDL_GetKeyboardState(NULL);
    
    // Move Forward and Backward
    if (keystate[SDL_SCANCODE_W]) state.camera.position.z += moveSpeed * dt;
    if (keystate[SDL_SCANCODE_S]) state.camera.position.z -= moveSpeed * dt;

    // Move Left and Right
    if (keystate[SDL_SCANCODE_A]) state.camera.position.x -= moveSpeed * dt;
    if (keystate[SDL_SCANCODE_D]) state.camera.position.x += moveSpeed * dt;

    // Move Up and Down
    if (keystate[SDL_SCANCODE_Q]) state.camera.position.y += moveSpeed * dt;
    if (keystate[SDL_SCANCODE_E]) state.camera.position.y -= moveSpeed * dt;

    // Camera
    if (keystate[SDL_SCANCODE_RIGHT])   state.camera.rotation.y += rotateSpeed * dt;
    if (keystate[SDL_SCANCODE_LEFT])    state.camera.rotation.y -= rotateSpeed * dt;
    if (keystate[SDL_SCANCODE_UP])      state.camera.rotation.x += rotateSpeed * dt;
    if (keystate[SDL_SCANCODE_DOWN])    state.camera.rotation.x -= rotateSpeed * dt;
}

