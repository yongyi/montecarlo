/*
 * Declaration.
 *
 * The Monte-Carlo simulation function to price a given option with given parameters,
 *      a given standard normal random number generator, with the option to perform
 *      control variate or moment matching (NOT both at the same time) variance reduction
 *      techniques. Returns the simulated price of the given option.
 *
 *
 * Yongyi Ye
 */

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

class MonteCarlo{

    private:
        double s;    // the underlying asset spot price
        double vol;  // sigma, volatility of the underlying asset
        double t;    // maturity of the option
        double r;    // risk neutral interest rate
        double q;    // continuous dividend rate
        double m;    // the number of steps wanted in each simulation (>1 for path-dependent options)

        Wrapper<Payoff> payoff;    // the payoff definition of an option
        Wrapper<Random> generator; // the random number generator

        /* indicators to use variance reduction techniques - default is FALSE */
        bool use_antithetic;        // indicator to use antithetic method or not
        bool use_control_variate;   // indicator to use control variate method or not
        bool use_moment_matching;   // indicator to use moment matching method or not

    public:
        /* monte-carlo simulation pricer */
        double price(int N);
        /*
         * inputs:
         * output:
         *      the simulated option price
         */

        /* monte carlo simulation for delta of PLAIN VANILLA options */
        double delta(int N, string type="call");
        /*
         * inputs:
         *      type - the option type, default is call
         *
         * output:
         *      the simulated option delta
         *
         */

        /* monte-carlo for vega of PLAIN VANILLA options */
        double vega(int N, string type="call");
        /*
         * inputs:
         *      type - the option type, default is call
         *
         * output:
         *      the simulated option vega
         *
         */

};

#endif
