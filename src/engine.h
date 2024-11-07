#ifndef ENGINE_H
#define ENGINE_H

#include "defs.h"

/* Types */
typedef struct {
    vec3_t pos;
    vec3_t rot;
    float fov;
} camera_t;

// TODO
typedef struct { void* _;
} scene_t;

typedef struct {
    void* window;     // Rendering context window
    camera_t camera;        // Current camera
    scene_t scene;          // Current scene
    int width, height;      // Window dimensions
    int quit;               // Has the user quit?
} engineState_t;

/* Variables */
extern engineState_t state;

/* Functions */
int engine_init(int width, int height, const char* title);

#endif
