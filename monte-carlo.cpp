/*
 * The Monte-Carlo simulation function to price a given option with given parameters,
 *      a given standard normal random number generator, with the option to perform
 *      control variate or moment matching (NOT both at the same time) variance reduction
 *      techniques. Returns the simulated price of the given option.
 *
 * Possible to be turned into a monte-carlo class in the future.
 *
 * Yongyi Ye
 */

#ifndef MONTECARLO_CPP
#define MONTECARLO_CPP

#include<assert.h>
#include<deque>
#include<math.h>
#include<string>

#include"random.hpp"
#include"statgatherer.hpp"
#include"payoff.hpp"
#include"wrapper.hpp"

using namespace std;

/************************************* function declarations *************************************/
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
 *      random - the random number generator
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
/***************************************** END **************************************************/

//namespace for the private function
namespace{

double get_b_hat(const deque<double>& s, const deque<double>& v){
/*
 * Function to calculate the b_hat value in the control variate technique
 * input: s - the controlling variate of the stock prices at maturity
 *        v - the option payoffs before adjustment
 * output: the b-hat value
 */
    assert(s.size() == v.size());
    int n = s.size();

    //get the mean values
    double s_mean = 0;
    double v_mean = 0;
    for(int i=0; i<n; i++){
        s_mean = s_mean + s[i];
        v_mean = v_mean + v[i];
    }
    s_mean = s_mean/n;
    v_mean = v_mean/n;

    //get the numerator and denominator
    double numerator = 0;
    double denominator = 0;
    for(int i=0; i<n; i++){
        numerator = numerator + (s[i]-s_mean)*(v[i]-v_mean);
        denominator = denominator + (s[i]-s_mean)*(s[i]-s_mean);
    }

    return numerator/denominator;
}

}

/**************************** start of function definition *******************************/

/* monte-carlo simulation pricer */
double monte_carlo(double s, double vol, double t, double r, double q, long n,
                    const Payoff& payoff, const Random& random,
                    bool use_control_variate, bool use_moment_matching){

/*
 * inputs:
 *      s - the underlying asset spot price
 *      vol - sigma, volatility of the underlying asset
 *      t - maturity of the option
 *      r - risk neutral interest rate
 *      q - continuous dividend rate
 *      n - the number of passes/simulations
 *      payoff - the payoff definition of an option
 *      random - the random number generator
 *      use_control_variate - indicator to use control variate method or not, default is false
 *      use_moment_matching - indicator to use moment matching method or not, default is false
 *
 * output:
 *      the simulated option price
 *
 */

    // the use_control_variate and use_moment_matching cannot both be true
    assert(!use_control_variate || !use_moment_matching);
    // the use_control_variate and use_moment_matching can be used only when the number of time steps
    //      for the simulation in one pass is 1, i.e. pricing vanilla options
    if(use_control_variate || use_moment_matching){ assert(random.get_step()==1); }
    assert(n>=1);

    // wrap the payoff and random number generator object so that the objects being passed
    //      in is not affected by whatever operations inside the function
    Wrapper<Payoff> payoff_ptr(payoff);
    Wrapper<Random> random_ptr(random);

    // the delta_t that should be used in the simulation - dt = t for vanilla options
    double dt = t/random_ptr->get_step();

    // the data containers
    StatGatherer gather;    //statistics gatherer
    deque<double> normal;   //store the normal random numbers generated
    deque<double> stockval; //store the intermediate stock values in one simulation
    deque<double> s_T;      //store the stock value at maturity, will be used only if variance reduction
                            //      methods are chosen


    for(int i=0; i<n; i++){
        //get the normal random numbers
        normal = random_ptr->get_normal();

        //get the simulated stock prices in one pass - the loop will not run if the time step is 1
        double s_stepwise = s * exp( (r-q-vol*vol/2.0)*dt + vol*sqrt(dt)*normal[0]);
        for(int j=1; j<normal.size(); j++){
            stockval.push_back(s_stepwise);
            s_stepwise = s_stepwise * exp( (r-q-vol*vol/2.0)*dt + vol*sqrt(dt)*normal[j]);
        }
        stockval.push_back(s_stepwise);

        //get the value at maturity
        s_T.push_back(stockval[stockval.size()-1]);

        //calculate the payoff for one pass and dump the result to the gatherer if moment-matching is no used
        if(!use_moment_matching){
            gather.dump_one_number(payoff_ptr->payoff(stockval));
        }

        //clear data, do another pass
        stockval.clear();
    }

    //control variate technique - the controlling variate is hard-coded
    if(use_control_variate){

        deque<double> result_old = gather.result_so_far();
        double b_hat = get_b_hat(s_T, result_old);

        //adjust the values, clear the gatherer, and push the new values into the gatherer
        gather.clear();

        double s_mean = exp(r*t) * s;
        for(int i=0; i<result_old.size(); i++){
            double adjusted = result_old[i] - b_hat * (s_T[i] - s_mean);
            gather.dump_one_number(adjusted);
        }
    }


    //moment matching technique - hard-coded as well
    if(use_moment_matching){
        //risk-neutral mean
        double s_mean_rn = exp(r*t) * s;

        //get the simulated value average
        double sum = 0;
        for(int i=0; i<s_T.size(); i++){ sum += s_T[i]; }
        double s_mean = sum/s_T.size();

        //adjust the stock prices
        for(int i=0; i<s_T.size(); i++){ s_T[i] = s_T[i] * s_mean_rn/s_mean; }

        //push the payoffs into the getherer
        gather.clear();
        deque<double> payoffval;
        for(int i=0; i<s_T.size(); i++){
            payoffval.clear();
            payoffval.push_back(s_T[i]);
            gather.dump_one_number(payoff_ptr->payoff(payoffval));
        }
    }

    return gather.mean();
}

/* monte carlo simulation for delta of plain vanilla options */
double monte_carlo_delta(double s, double k, double vol, double t, double r, double q,
                        long n, const Random& random, string type){

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

    //the method works for non-path-dependent options, i.e. vanilla options with 1 step in every simulation
    //      also make sure there is at least 1 simulation needed to be run
    assert(n>=1 && random.get_step()==1);
    assert(type=="call" || type=="put");

    // wrap the random number generator object so that the objects being passed
    //      in is not affected by whatever operations inside the function
    Wrapper<Random> random_ptr(random);

    // the data containers
    StatGatherer gather;    //statistics gatherer
    double normal;          //store the normal random number generated
    double delta;           //the simulated delta

    for(int i=0; i<n; i++){
        //get the normal random numbers
        normal = random_ptr->get_normal()[0];

        //get the simulated stock price
        double s_t = s * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*normal);

        if(type == "call" && s_t>k){
            delta = exp(-r*t) * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*normal);
            gather.dump_one_number(delta);
        }

        if(type == "put" && s_t<k){
            delta = exp(-r*t) * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*normal);
            gather.dump_one_number(delta);
        }
    }

    return gather.mean();
}

/* monte-carlo for vega of plain vanilla options */
double monte_carlo_vega(double s, double k, double vol, double t, double r, double q,
                        long n, const Random& random, string type){

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

    //the method works for non-path-dependent options, i.e. vanilla options with 1 step in every simulation
    //      also make sure there is at least 1 simulation needed to be run
    assert(n>=1 && random.get_step()==1);
    assert(type=="call" || type=="put");

    // wrap the random number generator object so that the objects being passed
    //      in is not affected by whatever operations inside the function
    Wrapper<Random> random_ptr(random);

    // the data containers
    StatGatherer gather;    //statistics gatherer
    double normal;          //store the normal random number generated
    double vega;            //the simulated vega

    for(int i=0; i<n; i++){
        //get the normal random numbers
        normal = random_ptr->get_normal()[0];

        //get the simulated stock price
        double s_t = s * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*normal);

        if(type == "call" && s_t>k){
            vega = exp(-r*t) * (-vol*t + sqrt(t)*normal)*s_t;
            gather.dump_one_number(vega);
        }

        if(type == "put" && s_t<k){
            vega = exp(-r*t) * (-vol*t + sqrt(t)*normal)*s_t;
            gather.dump_one_number(vega);
        }
    }

    return gather.mean();
}

#endif
