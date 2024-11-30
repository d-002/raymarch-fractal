#include "distance_estimator.h"
#include "complex.h"
#include "utils.h"

#define ITERATIONS 50
#define ESCAPE_RADIUS 256

double hypersphere_de(quat *q) {
    return 0;
}

double julia_de(quat *q) {
    complex z = { q->x, q->y };
    complex c = { q->z, q->w };

    complex dz = { 1, 0 };
    double r;

    for (int n = 0; n < ITERATIONS; n++) {
        r = comp_dot(z);
        if (r > ESCAPE_RADIUS) break;
        
        dz = comp_mul2add1(comp_mul(dz, z));

    }

    return 0;
}
