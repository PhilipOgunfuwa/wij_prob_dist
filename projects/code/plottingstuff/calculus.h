#ifndef CALCULUS_H
#define CALCULUS_H
#include <functional>

/*
The following are functions that calculate the integral between the lower and upper bound
of the continous probability density functions in continuous_prob.h. This is necessary for calculating the
Cumulative Density Function for them. 

The functions take a std::function<double(T, U, ...)> to act as a wrapper around the function pointer to the PDF simply
for readability. I could of done something like: double (*fcnPtr)(T, U). I may change this if I deem it necessary for optimization
(as there is some overhead since std::function<> is a object and not JUSt a pointer).

The function take the parameters for a given probability densitiy function, and the bounds to integrate between. I have a global
constexpr variable for the intervals to be 100,000 as I deem this to be more than accurate enough for calculating continous
distributions. Not only that but I believe that since I'm not using a rectangular (left, right, or midpoint) sum it will be even
more accurate.

General formula for trapezoidal sum
let h = (b - a)/n,
let b be the upper bound
let a be the lower bound
let n be the amount of intervals
let f(x) be the function to be integrated
let x_i = a + (i * h)

Approx integral = h * 0.5 * [ f(x_0) + 2(f(x_1) + f(x_2) + ... f(x_n-1)) + f(x_n) ]

These functions expect 1 or 2 parameters from the continous PDF's but they could easily be modified to work for general functions.

I will leave a function commented out at the bottom for anyone to use for general use.
*/

// Number of intervals/trapezoids 
constexpr int intervals { 100000 };

template <typename T, typename U>
double trapezoidal_sum(std::function<double(T, U)> func, T param1, double lower_bound, double upper_bound)
{
    assert(upper_bound > lower_bound && "Lower bound larger than or equal to upper bound");
    double area { 0 };
    double delta { (upper_bound - lower_bound) / intervals }; // this is our h
    double x_i { lower_bound }; 

    // Sum part of trapezoidal sum
    for (int i { 0 }; i < intervals; ++i)
    {
        area += (i != 0 && i != intervals-1) ? (2*func(param1, x_i)) : func(param1, x_i);
        x_i += delta;
    }

    area *= (delta / 2);

    return area;

}

template <typename T, typename U, typename V>
double trapezoidal_sum(std::function<double(T, U, V)>, T param1, U param2, double lower_bound, double upper_bound)
{
    double area { 0 };
    double delta { (upper_bound - lower_bound) / intervals };
    double x_i { 0 };

    // Sum part of trapezoidal sum
    for (int i { 0 }; i < intervals; ++i)
    {
        area += (i != 0 && i != intervals-1) ? (2*func(param1, param2, x_i)) : func(param1, param2, x_i);
        x_i += delta;
    }

    area *= (delta / 2);

    return area;
}


/* Implementation of trapezoidal sum on a simple 2D function
template <typename T>
double trapezoidal_sum(std::function<double(T)> func, double lower_bound, double upper_bound)
{
    assert(upper_bound > lower_bound && "Lower bound larger than or equal to upper bound");
    double area { 0 };
    double delta { (upper_bound - lower_bound) / intervals };
    double x_i { lower_bound };

    // Sum part of trapezoidal sum
    for (int i { 0 }; i < intervals; ++i)
    {
        area += (i != 0 && i != intervals-1) ? (2*func(x_i)) : func(x_i);
        x_i += delta;
    }

    area *= (delta / 2);

    return area;

}
*/

#endif
