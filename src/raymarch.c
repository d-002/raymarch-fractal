#include <math.h>
#include <stdint.h>

#include "raymarch.h"
#include "utils.h"
#include "postpro.h"

quat cam_pos = { -2, 0, 3, 0 };
//quat cam_pos = { 0, 0, 5, 0 };
// rotation: z/w, then around x axis, then around y axis
double cam_rot[3] = { 0, 0, 0 };

void ray(quat q, quat dir, struct ray_info *info, dist_estimator estimator) {
    double d = 1;
    double min_dist = d;
    long iterations = 0;

    while (d > THRESHOLD && qt_dot(q) < FAR) {
        d = estimator(q);
        if (d < min_dist) min_dist = d;
        q = qt_add(q, qt_mul(dir, d*0.5));

        iterations++;
    }

    info->hit = d <= THRESHOLD;
    info->min_dist = min_dist;
    info->iterations = iterations;
}

quat rotate(quat q) {
    return q;
}

void renderScene(uint32_t *pixels, dist_estimator estimator) {
    double fov = M_PI*FOV_DEG/180;
    double D = WIDTH/2/tan(fov/2);

    int w2 = WIDTH/2, h2 = HEIGHT/2;

    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++) {
            quat dir = { x-w2, y-h2, -D, 0 };
            dir = qt_norm(rotate(dir));

            struct ray_info info;
            ray(cam_pos, dir, &info, estimator);
            pixels[y*WIDTH + x] = getcol(&info);
        }
}
