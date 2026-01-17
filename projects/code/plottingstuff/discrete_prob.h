#ifndef DISCRETE_PROB_H
#define DISCRETE_PROB_H

#include <cmath>
#include <cassert>
#include <iostream>

// FIXME: Add Asserts to all functions


long long nChooseK(int n, int k)
{
    assert(n > 0 && "n less than or equal to 0");
    assert(k > 0 && "k less than or equal to 0");

    // If k is greater than n/2 
    // (thus n-k is less than k) to have less computations
    k = (k > n/2) ? n-k : k;

    long long result { 1 };

    // This is the iterative form of the C(n,k) formula
    // More efficient than calculating the factorials
    // independently
    for(int i { 1 }; i <= k; ++i)
        result = (result * (n - k + i)) / i; // always evaluates to an int (no worry of floating point divison)
                                    
    /*
    Mathematically works b/c
    C(n,k) = n*(n-1)*...*(n-k+1)
             -------------------
             k*(k-1)*...*1
    The numerator off result is working backwards 
    from n-k+1 back to one (as once i reachs k it will
    evaluated to (n - k + k) == (n)
   
    The denominator is working backwards as well as it
    is incrementing from 1 all the way to k!
    */

    return result;
}

double binomial_pdf(int trials, double prob, int successes)
{

    // FIXME:ASSERT
    /*
    formula
    trials = n, prob = p, successes = i)
    p(i) = nCi * p^i * (1-p)^(n-i)
    */
    return static_cast<double>(nChooseK(trials, successes)) *
           std::pow(prob, successes) *
           std::pow(1 - prob, trials - successes);
}

double poisson_pdf(double mean, int successes)
{
    // FIXME:ASSERT

    double mean_over_successes { 1 };

    /*
    formula
    mean = x, successes = i

    p(i) = ((e^-x) * x^i) / i!

    The loop works mathematically as it iteratively calculates (x^i) / i!

    The numerator can be written as
    ((e^-x) * (x * x * ...(i times)... * x))  
   
    The denominator can be written as
    (i * i-1 * i-2 * .... 1)
     
    mean_over_successes calculate that (x^i)/i!
    */
    
    for (int i { 1 }; i <= successes; ++i)
        mean_over_successes = (mean_over_successes * mean) / i;

    return std::exp(-mean) * mean_over_successes;

}

double geometric_pdf(double prob, int first_success) 
{
    //FIXME:ASSERT
    //FIXME:FORMULA
    // formula
    // prob = p, first_success = i
    // p(i) = p * (1 - p)^(i - 1), i = 1, 2, ...
    return std::pow(1 - prob, first_success - 1) * prob;
}

double neg_binomial_pdf(int rth_success, double prob, int trials)
{
    // FIXME:ASSERT
    // FIXME:FORMULA 

    return static_cast<double>(nChooseK(trials-1, rth_success-1)) *
           std::pow(prob, rth_success) *
           std::pow(1 - prob, trials - rth_success);
}

double hypergeometric_pdf(int sample_size, int pop_size, int success_in_pop, int success_in_sample)
{
    // FIXME:ASSERT
    // FIXME:FORMULA
    // make asserts for this
    return (static_cast<double>(nChooseK(success_in_pop, success_in_sample) *
            nChooseK(pop_size - success_in_pop, sample_size - success_in_sample))) /
           (static_cast<double>(nChooseK(pop_size, sample_size)));
}

#endif
