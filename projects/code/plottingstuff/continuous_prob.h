#ifndef CONTINUOUS_PROB_H
#define CONTINUOUS_PROB_H

#include <cmath>
#include <cassert>

double uniform_pdf(double lower_bound, double upper_bound, double x)
{
    return (lower_bound < x && x < upper_bound) ? (1 / (upper_bound - lower_bound)) : 0;
}

double normal_pdf(double mean, double sd, double x)
{
    constexpr double PI { 3.141592653589793 };
    return std::pow(std::sqrt(2 * PI) * sd, -1) * std::exp(-(x - mean)*(x - mean) / (2 * sd * sd));
}

double exponential_pdf(double lambda, double x)
{
    return (x >= 0.0) ? (lambda * std::exp(-lambda * x)) : 0.0;
}

#endif
