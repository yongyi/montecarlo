/*
 * Declaration.
 *
 * A Monte-Carlo simulation function to price a given option with given parameters
 *      and a given standard normal random number generator. The pricer first converts
 *      the N uniform random uniforms into AT MOST N random standard normals with a
 *      method of choice, then partition the normal numbers into n * m 2-D deque
 *      of doubles (n simulated path with m steps in each path) such that n * m <= N.
 *      (n * m == N if using inverse transformation method for generating normals).
 *
 * Because of the various methods used to generate standard normals from uniforms, the
 *      number of normals generated may be much less than the uniforms passed in.
 *
 * This Monte-Carlo pricer works with any given payoff functions passed in, regardless the
 *      option's path-dependency. It also provides an indicator to use the antithetic
 *      variance reduction technique.
 *
 * It returns the simulated price of the given option.
 *
 *
 * Yongyi Ye
 */

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include<deque>
#include"wrapper.hpp"
using namespace std;

class MonteCarloGeneral{

    private:
        double s;    // the underlying asset spot price
        double vol;  // sigma, volatility of the underlying asset
        double t;    // maturity of the option
        double r;    // risk neutral interest rate
        double q;    // continuous dividend rate

        Wrapper<Payoff> option;    // the payoff definition of an option
        Wrapper<Random> generator; // the random number generator

        bool use_antithetic;        // indicator to use antithetic method or not - default is FALSE

        /* helper function to preprocess the numbers got from the generator to partition them into n*m numbers*/
        deque< deque<double> > preprocess(int n, int m, const deque<double> &input);

    public:
        /* constructor */
        MonteCarloGeneral(double s_, double vol_, double t_, double r_, double q_,
                            const Payoff& option_, const Random& generator_,
                            bool use_antithetic_ = false);

        /* function to reset the generator */
        void reset_generator();

        /* monte-carlo simulation pricer */
        double price(int N, int m);
        /*inputs:N - the total number of uniform random numbers to be generated
         *       m - the number of steps wanted in each simulation (>1 for path-dependent options)
         * output:
         *      the simulated option price
         */

};

#endif
