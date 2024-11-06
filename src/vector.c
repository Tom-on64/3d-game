#include "defs.h"

inline vec_t vadd(const vec_t* a, const vec_t* b) {
    vec r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] + b->comp[i];
    }
    return r;
}

inline vec_t vsub(const vec_t* a, const vec_t* b) {
    vec r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] - b->comp[i];
    }
    return r;
}

inline vec_t vscale(const vec_t* a, int s) {
    vec r = *a;
    for (int i = 0; i < a->size; i++) {
        r.comp[i] = a->comp[i] * s;
    }
    return r;
}

inline double vdot(const vec_t* a, const vec_t* b) {
    double r = 0;
    for (int i = 0; i < a->size; i++) {
        r += a->comp[i] * b->comp[i];
    }
    return r;
}

inline double vmag(const vec_t* a) {
    return fsqrt(vdot(a, a));
}

inline vec_t vnorm(const vec_t* a) {
    double m = vmag(a);
    return (m != 0) ? vscale(a, 1.0/m) : *v;
}

inline void vprint(const vec_t* a) {
    printf("v%d( ", a->size);
    for (int i = 0; i < a->size; i++) {
        printf("%f ", a->comp[i]);
    }
    printf(")");
}

