#include "continuous_prob.h"
#include <iostream>
#include "calculus.h"

int main()
{
    std::function func { exponential_pdf };
    std::cout << trapezoidal_sum<double>(func, 10, 0.3) << '\n';
    return 0;
}

