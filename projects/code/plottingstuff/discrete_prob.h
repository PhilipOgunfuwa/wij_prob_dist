#ifndef DISCRETE_PROB_H
#define DISCRETE_PROB_H

#include <cmath>
#include <cassert>


double nChooseK(int n, int k)
{
    assert(k >= 0 && "Negative k");
    assert(n >= 1 && "0 or less n");
    assert(n >= k && "K larger than k");

    if (k == 0)
        return 1;
    if (k == 1)
        return n;

    // Symmetry law
    k = (k > n/2) ? n-k : k;

    double result { 1.0 };

    for(int i { 1 }; i <= k; ++i)
        result = (result * (n - k + i)) / i;

    return result;
}

double binomial_pmf(int trials, double prob, int successes)
{
    assert(trials >= successes && "More successes than trials");
    assert(0 <= prob && prob <= 1 && "Probability not within [0, 1]");

    return nChooseK(trials, successes) *
           std::pow(prob, successes) *
           std::pow(1-prob, trials - successes);
}

double poisson_pmf(double mean, int successes)
{
    assert(mean > 0 && "Mean less than 0");
    assert(successes >= 0 && "Negative successes");

    double mean_over_successes { 1 };
    
    for (int i { 1 }; i <= successes; ++i)
        mean_over_successes = (mean_over_successes * mean) / i;

    return std::exp(-mean) * mean_over_successes;
}

double geometric_pmf(double prob, int trial_of_first_success) 
{
    assert(trial_of_first_success >= 1 && "Negative successes, or 0 successes");
    assert(0 < prob && prob < 1 && "Probability not within (0, 1)");

    return std::pow(1 - prob, trial_of_first_success - 1) * prob;
}

double neg_binomial_pmf(int rth_success, double prob, int trials)
{
    assert(rth_success >= 1 && "Negative successes");
    assert(trials >= rth_success && "Not enough trials");
    assert(0 < prob && prob < 1 && "Probability not within (0, 1)");

    return nChooseK(trials-1, rth_success-1) *
           std::pow(prob, rth_success) *
           std::pow(1 - prob, trials - rth_success);
}

double hypergeometric_pmf(int sample_size, int pop_size, int success_in_pop, int success_in_sample)
{
    assert(sample_size <= pop_size && "Population size smaller than sample size");
    assert(success_in_sample <= success_in_pop && "More successes in sample than in population");

    return ((nChooseK(success_in_pop, success_in_sample) *
             nChooseK(pop_size - success_in_pop, sample_size - success_in_sample))) /
           ( nChooseK(pop_size, sample_size));
}

#endif
