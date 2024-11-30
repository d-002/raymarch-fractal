#ifndef RAYMARCH_H
#define RAYMARCH_H

#define THRESHOLD 0.01
#define FAR 1000

#include "quaternion.h"
#include "distance_estimator.h"

struct ray_info {
    int hit;
    double min_dist;
    long iterations;
};

void ray(quat, quat, struct ray_info *, dist_estimator);

#endif /* RAYMARCH_H */
