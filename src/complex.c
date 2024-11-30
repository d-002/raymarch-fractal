#include "complex.h"

complex comp_add(complex c1, complex c2) {
    return (complex){ c1.real + c2.real, c1.imag + c2.imag };
}

complex comp_sub(complex c1, complex c2) {
    return (complex){ c1.real - c2.real, c1.imag - c2.imag };
}

complex comp_mul(complex c1, complex c2) {
    return (complex) {
        c1.real * c2.real - c1.imag * c2.imag,
        c1.real * c2.imag + c1.imag * c2.real
    };
}

complex comp_mul2add1(complex c) {
    return (complex){ c.real * 2 + 1, c.imag * 2 + 1 };
}

double comp_dot(complex c) {
    return c.real * c.real + c.imag * c.imag;
}
