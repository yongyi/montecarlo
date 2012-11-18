/*
 * Declaration.
 *
 * The Monte-Carlo simulation function to price a given option with given parameters,
 *      a given standard normal random number generator, with the option to perform
 *      control variate or moment matching (NOT both at the same time) variance reduction
 *      techniques. Returns the simulated price of the given option.
 *
 * Possible to be turned into a monte-carlo class in the future.
 *
 * Yongyi Ye
 */

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP


/* monte-carlo simulation pricer */
double monte_carlo(double s, double vol, double t, double r, double q, long n,
                    const Payoff& payoff, const Random& random,
                    bool use_control_variate = false, bool use_moment_matching = false);
/*
 * inputs:
 *      s - the underlying asset spot price
 *      vol - sigma, volatility of the underlying asset
 *      t - maturity of the option
 *      r - risk neutral interest rate
 *      q - continuous dividend rate
 *      n - the number of passes/simulations
 *      payoff - the payoff definition of an option
 *      random - the random number generator (also contains the information of the number of normal random
 *                      numbers to be generated in one path of simulation)
 *      use_control_variate - indicator to use control variate method or not, default is false
 *      use_moment_matching - indicator to use moment matching method or not, default is false
 *
 * output:
 *      the simulated option price
 */

/* monte carlo simulation for delta of plain vanilla options */
double monte_carlo_delta(double s, double k, double vol, double t, double r, double q,
                        long n, const Random& random, string type="call");

/*
 * inputs:
 *      s - the underlying asset spot price
 *      k - option strike price
 *      vol - sigma, volatility of the underlying asset
 *      t - maturity of the option
 *      r - risk neutral interest rate
 *      q - continuous dividend rate
 *      n - the number of passes/simulations
 *      random - the random number generator
 *      type - the option type, default is call
 *
 * output:
 *      the simulated option delta
 *
 */

/* monte-carlo for vega of plain vanilla options */
double monte_carlo_vega(double s, double k, double vol, double t, double r, double q,
                        long n, const Random& random, string type="call");
/*
 * inputs:
 *      s - the underlying asset spot price
 *      k - option strike price
 *      vol - sigma, volatility of the underlying asset
 *      t - maturity of the option
 *      r - risk neutral interest rate
 *      q - continuous dividend rate
 *      n - the number of passes/simulations
 *      random - the random number generator
 *      type - the option type, default is call
 *
 * output:
 *      the simulated option vega
 *
 */

#endif