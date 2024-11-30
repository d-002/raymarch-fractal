#include "distance_estimator.h"
#include "complex.h"
#include "utils.h"

double hypersphere_de(quat *q) {
    return 0;
}

double julia_de(quat *q) {
    complex z = { q->x, q->y };
    complex c = { q->z, q->w };

    complex dz = { 1, 0 };
    double r = comp_dot(&z);

    return 0;
}
