#ifndef DISTANCE_ESTIMATOR_H
#define DISTANCE_ESTIMATOR_H

#include "quaternion.h"

typedef double (*dist_estimator)(quat);

double hypersphere_de(quat);
double julia_de(quat);

#endif /* DISTANCE_ESTIMATOR_H */
