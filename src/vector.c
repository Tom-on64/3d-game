#include "defs.h"

inline vec_t vadd(const vec_t* a, const vec_t* b) {
    ASSERT(a->size == b->size, "Vector sizes must match!\n");
    vec_t r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] + b->comp[i];
    }
    return r;
}

inline vec_t vsub(const vec_t* a, const vec_t* b) {
    ASSERT(a->size == b->size, "Vector sizes must match!\n");
    vec_t r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] - b->comp[i];
    }
    return r;
}

inline vec_t vscale(const vec_t* a, float s) {
    vec_t r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] * s;
    }
    return r;
}

inline float vdot(const vec_t* a, const vec_t* b) {
    ASSERT(a->size == b->size, "Vector sizes must match!\n");
    float r = 0;
    for (int i = 0; i < a->size; i++) {
        r += a->comp[i] * b->comp[i];
    }
    return r;
}

inline float vmag(const vec_t* a) {
    return sqrt(vdot(a, a));
}

inline vec_t vnorm(const vec_t* a) {
    float m = vmag(a);
    return (m != 0) ? vscale(a, 1.0/m) : *a;
}

inline void vprint(const vec_t* a) {
    printf("v%d( ", a->size);
    for (int i = 0; i < a->size; i++) {
        printf("%f ", a->comp[i]);
    }
    printf(")\n");
}

