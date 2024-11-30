#include "postpro.h"

uint32_t getcol(struct ray_info *info) {
    return info->hit ? 0xffffff : 0;
}
