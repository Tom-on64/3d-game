#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stddef.h>
#include "defs.h"

/* Types */

/*
 * This structure represents a mesh that can be rendered
 */
typedef struct {
    vec3_t* vertexList;
    vec2_t* edgeList;
    int vertexCount;
    int edgeCount;
} mesh_t;

/*
 * A gameobject
 */
typedef struct {
    vec3_t position;
    vec3_t rotation;
    vec3_t scale;
    mesh_t* mesh;
} gameobj_t;

/*
 * A camera that can be used to render from
 */
typedef struct {
    vec3_t position;
    vec3_t rotation;
    float fov;
    float nearClip;
    float farClip;
} camera_t;

typedef struct {
    int w;
    int h;
    SDL_Window* window;
    SDL_Renderer* renderer;
    camera_t camera;
} engineState_t;

extern engineState_t state;

#endif
