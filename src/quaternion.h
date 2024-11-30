#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct quat {
    double x, y, z, w;
} quat;

double qt_dot(quat *q1, quat *q2);
void qt_norm(quat *q);
void qt_add(quat *q1, quat *q2, quat *res);
void qt_sub(quat *q1, quat *q2, quat *res);
void qt_mul(quat *q1, double m, quat *res);

#endif /* QUATERNION_H */
