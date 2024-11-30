#include "complex.h"

void comp_add(complex *c1, complex *c2, complex *res) {
    res->real = c1->real + c2->real;
    res->imag = c1->imag + c2->imag;
}

void comp_sub(complex *c1, complex *c2, complex *res) {
    res->real = c1->real - c2->real;
    res->imag = c1->imag - c2->imag;
}

void comp_mul(complex *c1, complex *c2, complex *res) {
    res->real = c1->real * c2->real - c1->imag * c2->imag;
    res->imag = c1->real * c2->imag + c1->imag * c2->real;
}

void comp_scal_mul(complex *c1, double m, complex *res) {
    res->real *= m;
    res->imag *= m;
}

double comp_dot(complex *c) {
    return c->real * c->real + c->imag * c->imag;
}
