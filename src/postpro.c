#include "postpro.h"

#include <math.h>

#include "utils.h"

void getcol(struct ray_info *info, uint8_t *r, uint8_t *g, uint8_t *b) {
    double color;

    if (info->hit) {
        // ambient occlusion
        color = 2 / (1 + exp(-info->iterations / 100.0)) - 1;
        color = 1 - CLAMP(color, 0, 1);
    }
    else {
        // glow
        color = 0.2 * THRESHOLD/(info->min_dist);
    }

    uint8_t col = 255*color;
    *r = col;
    *g = col;
    *b = col;
}
