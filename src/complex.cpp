#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "complex.h"

/**
 * A collection of functions to do maths with complex numbers
 */

/**
 * @brief Returns the magnitude of the complex number
 */
double magnitude(complex x)
{
    return sqrt(x.a*x.a + x.b*x.b);
}

/**
 * @brief Returns the complex number that results from raising e 
 * to the power of the input paramater multiplied by i (imaginary unit)
 */
complex im_exp(double x)
{
    complex return_var = {cos(x), sin(x)};
    return return_var;
}

/**
 * @brief Returns the sum of the two opperands
*/
complex add(complex x, complex y)
{
    complex return_var = {x.a + y.a, x.b + y.b};
    return return_var;
}

/**
 * @brief Returns the product of the two opperands
 */
complex multiply(complex x, complex y)
{
    double a=x.a, b=x.b, c=y.a, d=y.b;
    complex return_var = {a*c-b*d, a*d+b*c};
    return return_var;
}

/**
 * @brief result = x - y
 */
complex subtract(complex x, complex y)
{
    return (complex){x.a-y.a, x.b-y.b};
}

/**
 * @brief Prints a complex number without a carrage return in the using the following format:
 * (a+bi) ==> Where a and b are the respective real and imaginary components
 */
void print_complex(complex num)
{
    Serial.printf("(%.2f+%.2fi)", num.a, num.b);
}
