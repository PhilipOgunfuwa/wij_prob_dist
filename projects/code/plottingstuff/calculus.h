#ifndef CALCULUS_H
#define CALCULUS_H
#include <functional>

double ftc_integral(double x1, double x2, std::function<double(double)> func)
{
    // Func is expected to already be integrated
    return func(x2) - func(x1);
}

double reimann_sum(double x1, double x2, std::function<double(double)> func)
{
    
}
#endif
