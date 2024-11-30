#ifndef RAYMARCH_H
#define RAYMARCH_H

#define THRESHOLD 0.01
#define FAR 1000
#define FOV_DEG 90

#include "quaternion.h"
#include "distance_estimator.h"

struct ray_info {
    int hit;
    double min_dist;
    long iterations;
};

void renderScene(uint32_t *, dist_estimator);

#endif /* RAYMARCH_H */
