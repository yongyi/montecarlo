/*
 * Declaration.
 *
 * A Monte-Carlo simulation function to price a given vanilla European option with
 *      given parameters and a given standard normal random number generator.
 *      The pricer first converts the N uniform random uniforms into AT MOST N
 *      random standard normals with a method of choice, then runs the simulation with
 *      chosen variance reduction treatments with each simulation of timestep 1.
 *      (Since vanilla options are path-independent.)
 *
 * Because of the various methods used to generate standard normals from uniforms, the
 *      number of normals generated may be much less than the uniforms passed in.
 *
 * This Monte-Carlo pricer works ONLY for European options (put/call) to compute its
 *      price, delta, and vega.
 *
 * Yongyi Ye
 */

#ifndef MONTECARLOVANILLA_HPP
#define MONTECARLOVANILLA_HPP

#include<deque>
#include<string>
using namespace std;

class MonteCarloVanilla{

    private:
        double s;    // the underlying asset spot price
        double k;    // the strike of the option
        double vol;  // sigma, volatility of the underlying asset
        double t;    // maturity of the option
        double r;    // risk neutral interest rate
        double q;    // continuous dividend rate
        string type; // the type of the European option - put/call

        Wrapper<Random> generator; // the random number generator

        /* indicators to use variance reduction techniques - default is FALSE */
        bool use_antithetic;        // indicator to use antithetic method or not
        bool use_control_variate;   // indicator to use control variate method or not
        bool use_moment_matching;   // indicator to use moment matching method or not

        /* numbers to be assigned after the simulation */
        double price;
        double delta;
        double vega;

        /***** private Monte-Carlo functions ******/

        void compute_price(const deque<double> &normals);
        /* monte-carlo simulation pricer for PLAIN VANILLA options
         * inputs: N - the total number of uniform random numbers to be generated
         * output: the simulated option delta
         */

        void compute_delta(const deque<double> &normals);
        /* monte carlo simulation for delta of PLAIN VANILLA options
         * inputs: N - the total number of uniform random numbers to be generated
         * output: the simulated option price
         */

        void compute_vega(const deque<double> &normals);
        /* monte-carlo for vega of PLAIN VANILLA options
         * inputs: N - the total number of uniform random numbers to be generated
         * output: the simulated option vega
         */

        /* antithetic treatment of the data */
        void antithetic_treatment(deque<double> &normals);
        /* control-variate treatment of the data */
        void control_variate_treatment(deque<double> &stockvals, deque<double> &payoffs);
        /* moment-matching treatment of the data */
        void moment_matching_treatment(deque<double> &stockvals);
        /* get the mean of a sequence of numbers */
        double mean(const deque<double> &input);

    public:
        /* constructor */
        MonteCarloVanilla(double s_, double k_, double vol_, double t_, double r_, double q_, string type_,
                             const Random& generator_, bool use_antithetic_ = false,
                             bool use_control_variate_ = false, bool use_moment_matching_ = false);

        /* function to reset the generator */
        void reset_generator();

        void run_monte_carlo(int N);
        /* function to run the monte-carlo pricer, delta/vega calculator at the same time
         * with a given number of uniforms wanted to generate random normals using the generator.
         *
         * input: N - the parameter to be passed into the generator's get_normal() function
         * output: no output, updates the options price, delta, vega
         */

        /* getter functions for the parameters */
        double get_price();
        double get_delta();
        double get_vega();

};

#endif
