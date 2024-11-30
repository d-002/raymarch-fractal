#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct quat {
    double x, y, z, w;
} quat;

double qt_dot(quat, quat);
quat qt_norm(quat);
quat qt_add(quat, quat);
quat qt_sub(quat, quat);
quat qt_mul(quat, double);

#endif /* QUATERNION_H */
