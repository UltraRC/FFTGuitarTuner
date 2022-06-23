#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdint.h>

typedef struct {
    double a; double b;
} complex;

complex im_exp(double x);
double magnitude(complex x);
complex add(complex x, complex y);
complex subtract(complex x, complex y);
complex multiply(complex x, complex y);
void print_complex(complex num);

#endif // COMPLEX_H