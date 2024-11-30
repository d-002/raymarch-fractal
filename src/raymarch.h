#ifndef RAYMARCH_H
#define RAYMARCH_H

#define THRESHOLD 0.01
#define FAR2 1000

#include "quaternion.h"

struct ray_info {
    int hit;
    double min_dist;
    long iterations;
};

void ray(quat, quat, struct ray_info *);

#endif /* RAYMARCH_H */
