#include <math.h>

#include "postpro.h"
#include "utils.h"

uint32_t getcol(struct ray_info *info) {
    if (info->hit) {
        // ambient occlusion
        double occl = 2 / (1 + exp(-info->iterations / 30.0)) - 1;
        occl = CLAMP(occl, 0, 1);

        return ((uint8_t)(255 - 255*occl)) * 0x10101;
    }

    // glow
    return 0;
}
