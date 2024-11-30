#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct quat {
    double x, y, z, w;
} quat;

double qt_dot(quat *q1, quat *q2);
double qt_add(quat *q1, quat *q2, quat *res);
double qt_sub(quat *q1, quat *q2, quat *res);
double qt_mul(quat *q1, double m, quat *res);

#endif /* QUATERNION_H */
