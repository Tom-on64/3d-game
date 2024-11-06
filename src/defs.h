#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Macros
#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

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
    double comp[4];
} vec_t;

#define v2(_x, _y)          ((vec_t){ .size = 2, .comp = { (_x), (_y) }})
#define v3(_x, _y, _z)      ((vec_t){ .size = 3, .comp = { (_x), (_y), (_z) }})
#define v4(_x, _y, _z, _w)  ((vec_t){ .size = 4, .comp = { (_x), (_y), (_z), (_w) }})

inline vec_t    vadd    (const vec_t* a, const vec_t* b);
inline vec_t    vsub    (const vec_t* a, const vec_t* b);
inline vec_t    vscale  (const vec_t* a, int s);
inline double   vdot    (const vec_t* a, const vec_t* b);
inline double   vmag    (const vec_t* a);
inline vec_t    vnorm   (const vec_t* a);
inline void     vprint  (const vec_t* a);

#endif
