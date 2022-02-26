/*
DADA function definitions
*/

#include <iostream>
#include <cmath>
#include "dada.h"
using std::cout, std::endl, std::abs, std::sqrt, std::pow;

int amax(const double x[], const unsigned int len)
{
    //TODO: student implement code heres
    //index of first element of input vector with maximum absolute value, or -1 if vector is empty
    double max = abs(x[0]);
    int max_index = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        if (abs(x[i]) > max)
        {
            max = abs(x[i]);
            max_index = i;
        }
    }
    if (len == 0)
        return -1;
    else
        return max_index;
}

double asum(const double x[], const unsigned int len)
{
    //TODO: student implement code here
    double sum = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        sum += abs(x[i]);
    }
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len)
{
    //TODO: student implement code here
    /**
     * Add scalar multiple of vector to input vector: ȳ = a*x̄ + ȳ
     * @param   a       scalar multiple of input vector x
     * @param   x       input vector x
     * @param   y       input vector y
     * @param   len     length of input vectors
    */
    for (unsigned int i = 0; i < len; i++)
    {
        y[i] += (a * x[i]);
    }
}

void copy(const double src[], double dest[], const unsigned int len)
{
    //TODO: student implement code here
    /**
     * Copy input vector x into input vector y.
     * @param   src     input source vector
     * @param   dest    input destination vector
     * @param   len     length of input vectors
    */
    for (unsigned int i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}

double dot(const double x[], const double y[], const unsigned int len)
{
    /**
     * Calculate dot product of two input vectors.
     * @param   x       input vector x
     * @param   y       input vector y
     * @param   len     length of input vectors
     * @return          doct product of two input vectors
     */
    //TODO: student implement code here
    int sum = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        sum += (x[i] * y[i]);
    }

    return sum;
}

double norm2(const double x[], const unsigned int len)
{
    /**
     * Calculate Euclidean norm (i.e., magnitude, length) of input vector.
     * @param   x       input vector
     * @param   len     length of input vector
     * @return          Euclidean norm of input vector
     */
    double sum = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        sum += pow(x[i], 2);
    }

    return (sqrt(sum)); //TODO: student implement code here
}

void scale(const double a, double x[], const unsigned int len)
{
    /**
     * Multiply input vector by a scalar: x̄ = a*x̄
     * @param   a   input scalar
     * @param   x   input vector
     */
    //TODO: student implement code here
    for (unsigned int i = 0; i < len; i++)
    {
        x[i] = (a * x[i]);
    }
}

void swap(double x[], double y[], const unsigned int len)
{
    /**
     * Swap element values between input vectors x and y.
     * @param   x   input vector x
     * @param   y   input vector y
     */
    //TODO: student implement code here
    int temp = 0;
    for (unsigned int i = 0; i < len; i++)
    {
        temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}
