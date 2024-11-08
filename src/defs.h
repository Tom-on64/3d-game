#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Macros
#define ASSERT(_e, ...) \
        if (!(_e)) {\
            fprintf(stderr, "[%s:%d] Assert() ", __FILE__, __LINE__);\
            fprintf(stderr, __VA_ARGS__);\
            exit(1);\
        }

// Constants
#define PI      3.14159265358979
#define TAU     (PI * 2.0)
#define PI_2    (PI / 2.0)
#define PI_4    (PI / 4.0)

#define DEG2RAD(_n) ((_n) * (PI / 180.0))
#define RAD2DEG(_n) ((_n) * (180.0 / PI))

// Vectors
typedef struct {
    int size;
    union {
        struct { float x, y, z, w; };   
        float comp[4];
    };
} vec_t;
typedef vec_t vec2_t;
typedef vec_t vec3_t;
typedef vec_t vec4_t;

#define vec2(_x, _y)            ((vec2_t){ .size = 2, .comp = { (_x), (_y) }})
#define vec3(_x, _y, _z)        ((vec3_t){ .size = 3, .comp = { (_x), (_y), (_z) }})
#define vec4(_x, _y, _z, _w)    ((vec4_t){ .size = 4, .comp = { (_x), (_y), (_z), (_w) }})

vec_t vadd   (const vec_t* a, const vec_t* b);
vec_t vsub   (const vec_t* a, const vec_t* b);
vec_t vscale (const vec_t* a, float s);
float vdot   (const vec_t* a, const vec_t* b);
float vmag   (const vec_t* a);
vec_t vnorm  (const vec_t* a);
void  vprint (const vec_t* a);

// Matricies
typedef struct {
    float m[4*4];   // 4x4 Matrix
} mat4_t;

#define mat4_identity()     ((mat4_t) { .m = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} })                
#define mat4_translate(_t)  ((mat4_t) { .m = { 1.0f, 0.0f, 0.0f, t.x, 0.0f, 1.0f, 0.0f, t.y, 0.0f, 0.0f, 1.0f, t.z, 0.0f, 0.0f, 0.0f, 1.0f} })
#define mat4_scale(_s)      ((mat4_t) { .m = { s.x, 0.0f, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, 0.0f, s.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} })
#define mat4_rotx(_a)       ((mat4_t) { .m = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos(a), -sin(a), 0.0f, 0.0f, sin(a), cos(a), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} })
#define mat4_roty(_a)       ((mat4_t) { .m = { cos(a), 0.0f, sin(a), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -sin(a), 0.0f, cos(a), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} })
#define mat4_rotz(_a)       ((mat4_t) { .m = { cos(a), -sin(a), 0.0f, 0.0f, sin(a), cos(a), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} })

mat4_t  m4mult  (const mat4_t* a, const mat4_t* b);
vec4_t  m4vmult (const mat4_t* a, const vec4_t* b);
void    m4print (const mat4_t* a);

// Some math stuff
inline double lerp(double a, double b, double t) { return t*b + (1.0-t) * a; }

#endif
