#include <math.h>

#include "quaternion.h"

double qt_dot(quat q) {
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

quat qt_norm(quat q) {
    double invLength = 1 / sqrt(qt_dot(q));
    return (quat) {
        q.x * invLength,
        q.y * invLength,
        q.z * invLength,
        q.w * invLength
    };
}

quat qt_add(quat q1, quat q2) {
    return (quat) {
        q1.x + q2.x,
        q1.y + q2.y,
        q1.z + q2.z,
        q1.w + q2.w
    };
}

quat qt_sub(quat q1, quat q2) {
    return (quat) {
        q1.x - q2.x,
        q1.y - q2.y,
        q1.z - q2.z,
        q1.w - q2.w
    };
}

quat qt_mul(quat q, double m) {
    return (quat) {
        q.x * m,
        q.y * m,
        q.z * m,
        q.w * m
    };
}
