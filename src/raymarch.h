#ifndef RAYMARCH_H
#define RAYMARCH_H

#define THRESHOLD 0.0001
#define FAR 1000
#define FOV_DEG 90

#include "quaternion.h"
#include "distance_estimator.h"

extern int res;

struct camera {
    quat pos;
    // rotation: z/w, then around x axis, then around y axis
    double rot[3];
};

struct ray_info {
    int hit;
    double min_dist;
    long iterations;
};

void renderScene(uint32_t *, dist_estimator, struct camera *);

#endif /* RAYMARCH_H */
