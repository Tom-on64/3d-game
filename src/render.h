#ifndef RENDER_H
#define RENDER_H

#include "engine.h"
#include "defs.h"

vec2_t project(vec3_t point);
void drawMesh(const gameobj_t* obj);
void drawFrame();

#endif
