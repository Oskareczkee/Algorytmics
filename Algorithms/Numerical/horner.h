#pragma once
#include <math.h>

/*
    Calculates polynomial of given degree and coeficcients, for given value
*/
inline double horner_calculate_polynomial(double* coeficcients, const int& degree, const double& value)
{
    double output =0;
    for(int x=degree-1;x>=0;x--)
        output = coeficcients[x] + value * output; //f(x) = a0 + x(a1 +x (a2 +x ...))

    return output;
}

/*
    Calculates polynomial of given degree and coeficcients, for given value
    pow - uses powers to calculate each term separetely
    This algorithm should be slightly slower, due to the use of pow function
*/
inline double horner_calculate_polynomial_pow(double* coeficcients, const int& degree, const double& value)
{
    double output = 0;
    for(int x = degree-1;x>=0;x--)
        output += coeficcients[x]  * pow(value, degree-x);

    return output;
}