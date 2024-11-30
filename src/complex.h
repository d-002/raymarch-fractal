#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct complex {
    double real, imag;
} complex;

void comp_add(complex *c1, complex *c2, complex *res);
void comp_sub(complex *c1, complex *c2, complex *res);
void comp_mul(complex *c1, complex *c2, complex *res);
void comp_scal_mul(complex *c1, double m, complex *res);
double comp_dot(complex *c);

#endif /* COMPLEX_H */
