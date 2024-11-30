#include <math.h>

#include "postpro.h"
#include "utils.h"

uint32_t getcol(struct ray_info *info) {
    double color;

    if (info->hit) {
        // ambient occlusion
        color = 2 / (1 + exp(-info->iterations / 30.0)) - 1;
        color = 1 - CLAMP(color, 0, 1);
    }
    else {
        // glow
        color = 0.2 * THRESHOLD/(info->min_dist);
    }

    return ((uint8_t)(255*color)) * 0x10101;
}
