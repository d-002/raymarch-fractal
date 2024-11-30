#include <math.h>

#include "quaternion.h"

double qt_dot(quat *q1, quat *q2) {
    return q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;
}

void qt_norm(quat *q) {
    double invLength = 1 / sqrt(qt_dot(q, q));
    q->x *= invLength;
    q->y *= invLength;
    q->z *= invLength;
    q->w *= invLength;
}

void qt_add(quat *q1, quat *q2, quat *res) {
    res->x = q1->x + q2->x;
    res->y = q1->y + q2->y;
    res->z = q1->z + q2->z;
    res->w = q1->w + q2->w;
}

void qt_sub(quat *q1, quat *q2, quat *res) {
    res->x = q1->x - q2->x;
    res->y = q1->y - q2->y;
    res->z = q1->z - q2->z;
    res->w = q1->w - q2->w;
}

void qt_mul(quat *q1, double m, quat *res) {
    res->x = q1->x * m;
    res->y = q1->y * m;
    res->z = q1->z * m;
    res->w = q1->w * m;
}
