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
    // rotate quaternion depending on the camera rotations
    // input quaternion should be normalized and have its w component to 0

    ///// TODO: cache cos and sin

    double x, y, z;
    z = q.z;
    double c0 = cos(cam_rot[0]), s0 = sin(cam_rot[0]);
    q.z = z*c0;
    q.w = z*s0;

    y = q.y;
    z = q.z;
    double c1 = cos(cam_rot[1]), s1 = sin(cam_rot[1]);
    q.y = y*c1 - z*s1;
    q.z = z*c1 + y*s1;

    x = q.x;
    z = q.z;
    double c2 = cos(cam_rot[2]), s2 = sin(cam_rot[2]);
    q.x = x*c2 + z*s2;
    q.z = z*c2 - x*s2;

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
