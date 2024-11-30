#include "raymarch.h"

void ray(quat q, quat dir, struct ray_info *info, dist_estimator estimator) {
    double d = 1;
    double min_dist = d;
    long iterations = 0;

    while (d > THRESHOLD && qt_dot(q) < FAR) {
        d = estimator(q);
        if (d < min_dist) min_dist = d;
        q = qt_add(q, qt_mul(dir, d));

        iterations++;
    }

    info->hit = d <= THRESHOLD;
    info->min_dist = min_dist;
    info->iterations = iterations;
}

