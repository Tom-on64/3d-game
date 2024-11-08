#include <SDL2/SDL.h>
#include <math.h>
#include "render.h"
#include "defs.h"

extern gameobj_t cube;

vec3_t rotx(vec3_t p, float angle);
vec3_t roty(vec3_t p, float angle);
vec3_t rotz(vec3_t p, float angle);

void drawFrame() {
    // Clear
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);

    drawMesh(&cube);

    // Draw to the screen
    SDL_RenderPresent(state.renderer);
}

void drawMesh(const gameobj_t* obj) {
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < obj->mesh->edgeCount; i++) {
        const vec2_t edge = obj->mesh->edgeList[i];
        vec3_t start = obj->mesh->vertexList[(int)edge.x];
        vec3_t end = obj->mesh->vertexList[(int)edge.y];

        // Translate
        start.x += obj->position.x;
        start.y += obj->position.y;
        start.z += obj->position.z;
        end.x += obj->position.x;
        end.y += obj->position.y;
        end.z += obj->position.z;

        // Rotate
        start = rotx(start, obj->rotation.x);
        start = roty(start, obj->rotation.y);
        start = rotz(start, obj->rotation.z);
        end = rotx(end, obj->rotation.x);
        end = roty(end, obj->rotation.y);
        end = rotz(end, obj->rotation.z);

        // Project
        vec2_t startp = project(start);
        vec2_t endp = project(end);
        SDL_RenderDrawLine(state.renderer, startp.x, startp.y, endp.x, endp.y);
    }
}

vec2_t project(vec3_t point) {
    // Translate point relative to camera position
    vec3_t p = vec3(
        point.x - state.camera.position.x,
        point.y - state.camera.position.y,
        point.z - state.camera.position.z
    );

    p = rotx(p, state.camera.rotation.x);
    p = roty(p, state.camera.rotation.y);  
    p = rotz(p, state.camera.rotation.z);

    // Perspective projection
    float fov = state.camera.fov;
    float scale = 100.0; //(state.w / 2.0) / tan(DEG2RAD(state.camera.fov) * 0.5);
    return vec2(
        state.w / 2 + (fov * p.x) / (fov + p.z) * scale,
        state.h / 2 + (fov * p.y) / (fov + p.z) * scale
    );
}

/* TODO: Move these elsewhere */
vec3_t rotx(vec3_t p, float angle) {
    // Rotate point p around the X axis by 'angle'
    vec3_t out;
    out.x = p.x;
    out.y = cos(angle) * p.y - sin(angle) * p.z;
    out.z = sin(angle) * p.y + cos(angle) * p.z;
    return out;
}

vec3_t roty(vec3_t p, float angle) {
    // Rotate point p around the Y axis by 'angle'
    vec3_t out;
    out.x = cos(angle) * p.x + sin(angle) * p.z;
    out.y = p.y;
    out.z = -sin(angle) * p.x + cos(angle) * p.z;
    return out;
}

vec3_t rotz(vec3_t p, float angle) {
    // Rotate point p around the Z axis by 'angle'
    vec3_t out;
    out.x = cos(angle) * p.x - sin(angle) * p.y;
    out.y = sin(angle) * p.x + cos(angle) * p.y;
    out.z = p.z;
    return out;
}

