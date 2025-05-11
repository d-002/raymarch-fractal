#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex {
    double real, imag;
} complex;

complex comp_add(complex, complex);
complex comp_sub(complex, complex);
complex comp_mul(complex, complex);
complex comp_mul2add1(complex);
double comp_dot(complex);

#endif /* COMPLEX_H */
