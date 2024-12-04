#include "raymarch.h"

#include <math.h>

#include "utils.h"
#include "postpro.h"

int res = 4;

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

quat rotate(quat q, double *rot) {
    // rotate quaternion depending on the camera rotations
    // input quaternion should be normalized and have its w component to 0

    ///// TODO: cache cos and sin

    double x, y, z;
    z = q.z;
    double c0 = cos(rot[0]), s0 = sin(rot[0]);
    q.z = z*c0;
    q.w = z*s0;

    y = q.y;
    z = q.z;
    double c1 = cos(rot[1]), s1 = sin(rot[1]);
    q.y = y*c1 - z*s1;
    q.z = z*c1 + y*s1;

    x = q.x;
    z = q.z;
    double c2 = cos(rot[2]), s2 = sin(rot[2]);
    q.x = x*c2 + z*s2;
    q.z = z*c2 - x*s2;

    return q;
}

void renderScene(uint32_t *pixels, dist_estimator estimator, struct camera *cam) {
    double fov = M_PI*FOV_DEG/180;
    double D = WIDTH/2/tan(fov/2);

    int w2 = WIDTH/2, h2 = HEIGHT/2;

    for (int x = 0; x < WIDTH; x += res)
        for (int y = 0; y < HEIGHT; y += res) {
            quat dir = { x-w2, h2-y, -D, 0 };
            dir = qt_norm(rotate(dir, cam->rot));

            struct ray_info info;
            ray(cam->pos, dir, &info, estimator);

            uint32_t col = getcol(&info);
            //pixels[y*WIDTH + x] = col;
            for (int dx = 0; dx < res; dx++)
                for (int dy = 0; dy < res; dy++)
                    pixels[(y+dy)*WIDTH + x+dx] = col;
        }
}
