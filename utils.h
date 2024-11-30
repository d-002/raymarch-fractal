#ifndef UTILS_H
#define UTILS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_TAU
#define M_TAU 6.28318530717958647692
#endif

#define WIDTH 640
#define HEIGHT 480
#define FPS 60

// avoid warnings
void usleep(unsigned int);

double tstamp();

#endif /* UTILS_H */
