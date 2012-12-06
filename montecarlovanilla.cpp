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

#include<assert.h>
#include<deque>
#include<math.h>
#include<string>

#include"random.hpp"
#include"statgatherer.hpp"
#include"payoff.hpp"
#include"wrapper.hpp"
#include"montecarlovanilla.hpp"

using namespace std;

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

/**************************** start of definition *******************************/

MonteCarloVanilla::MonteCarloVanilla(double s_, double k_, double vol_, double t_, double r_, double q_, string type_,
                                        const Random& generator_, bool use_antithetic_, bool use_control_variate_,
                                        bool use_moment_matching_):
                                    s(s_), k(k_), vol(vol_), t(t_), r(r_), q(q_), type(type_), generator(generator_),
                                    use_antithetic(use_antithetic_), use_control_variate(use_control_variate_),
                                    use_moment_matching(use_moment_matching_),
                                    price(-10), delta(-10), vega(-10){

    assert(use_antithetic + use_control_variate + use_moment_matching <= 1);
}

void MonteCarloVanilla::reset_generator(){
    generator->reset();
}

/* getter functions */
double MonteCarloVanilla::get_price(){
    return price;
}

double MonteCarloVanilla::get_delta(){
    return delta;
}

double MonteCarloVanilla::get_vega(){
    return vega;
}

/* function to run the monte-carlo function */
void MonteCarloVanilla::run_monte_carlo(int N){
    deque<double> normals(generator->get_normal(N));
    if(use_antithetic){ antithetic_treatment(normals); }

    compute_price(normals);
    compute_delta(normals);
    compute_vega(normals);
    return;
}

/* Monte-Carlo simulations */

void MonteCarloVanilla::compute_price(const deque<double> &normals){
/* monte-carlo simulation pricer for PLAIN VANILLA options
 * inputs: N - the total number of uniform random numbers to be generated
 * output: the simulated option delta
 */

    int n = normals.size();
    //risk-free discount factor
    double discount = exp(-r*t);

    // the data containers
    StatGatherer gather;    // statistics gatherer
    deque<double> stockval; // store the stock value at maturity
    deque<double> payoffs;  // the payoff of the option in each simulation
    double one_normal;      // one generated normal number
    double one_s;           // one simulated stock value

    for(int i=0; i<n; i++){
        one_normal = normals[i];
        double one_s = s * exp( (r-q-vol*vol/2.0)*t + vol*sqrt(t)*one_normal);
        stockval.push_back(one_s);
    }


    if(use_moment_matching){ moment_matching_treatment(stockval); }

    for(int i=0; i<n; i++){
        if(type == "call"){ payoffs.push_back( max<double>(stockval[i] - k, 0)); }
        if(type == "put"){ payoffs.push_back( max<double>(k - stockval[i], 0)); }
    }

    if(use_control_variate){ control_variate_treatment(stockval, payoffs); }

    price = mean(payoffs);
}


void MonteCarloVanilla::compute_delta(const deque<double> &normals){
/* monte carlo simulation for delta of PLAIN VANILLA options
 * inputs: N - the total number of uniform random numbers to be generated
 * output: the simulated option price
 */

    int n = normals.size();
    // the data containers
    deque<double> deltas;   // collection of deltas
    double one_delta;       // one simulated delta
    double one_normal;      // one generated normal number

    for(int i=0; i<n; i++){
        one_normal = normals[i];

        //get the simulated stock price
        double s_t = s * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*one_normal);

        if(type == "call" && s_t>k){
            one_delta = exp(-r*t) * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*one_normal);
            deltas.push_back(one_delta);
        }
        if(type == "put" && s_t<k){
            one_delta = exp(-r*t) * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*one_normal);
            deltas.push_back(one_delta);
        }
    }
    delta = mean(deltas);
}

void MonteCarloVanilla::compute_vega(const deque<double> &normals){
/* monte-carlo for vega of PLAIN VANILLA options
 * inputs: N - the total number of uniform random numbers to be generated
 * output: the simulated option vega
 */

    int n = normals.size();

    // the data containers
    deque<double> vegas;     // collection of vegas
    double one_vega;        // one simulated vega
    double one_normal;      // one generated normal number

    for(int i=0; i<n; i++){
        one_normal = normals[i];

        //get the simulated stock price
        double s_t = s * exp((r-q-vol*vol/2.0)*t + vol*sqrt(t)*one_normal);

        if(type == "call" && s_t>k){
            one_vega = exp(-r*t) * (-vol*t + sqrt(t)*one_normal)*s_t;
            vegas.push_back(one_vega);
        }

        if(type == "put" && s_t<k){
            one_vega = exp(-r*t) * (-vol*t + sqrt(t)*one_normal)*s_t;
            vegas.push_back(one_vega);
        }
    }

    vega = mean(vegas);
}

void MonteCarloVanilla::antithetic_treatment(deque<double> &normals){
/*
 * function to do the antithetic treatment to the random normals generated such that
 * the negative of every standard normals that has been generated should also be
 * in the normal number sequence
 */
    int n = normals.size(); // size before the change

    //make changes on the deque of normals directly
    for(int i=0; i<n; i++){ normals.push_back(-normals[i]); }
    return;
}

void MonteCarloVanilla::control_variate_treatment(deque<double> &stockvals, deque<double> &payoffs){
/* control variate technique - the controlling variate is hard-coded as the stock price
 * the changes is going to be made on the deque of payoffs directly
 */
    double b_hat = get_b_hat(stockvals, payoffs);

    //the risk-neutral expected value
    double s_mean = exp(r*t) * s;

    for(int i=0; i<payoffs.size(); i++){
        payoffs[i] = payoffs[i] - b_hat * (stockvals[i] - s_mean);
    }
    return;
}

void MonteCarloVanilla::moment_matching_treatment(deque<double> &stockvals){
/* moment matching technique - hard-coded as well - it matches the first moment of the stock prices
 * the changes will be made on the deque of stockvals directly
 */
    // risk-neutral mean
    double s_mean_rn = exp(r*t) * s;
    // the simulated value average
    double s_mean = mean(stockvals);

    //adjust the stock prices
    for(int i=0; i<stockvals.size(); i++){ stockvals[i] = stockvals[i] * s_mean_rn/s_mean; }
    return;
}

double MonteCarloVanilla::mean(const deque<double> &input){
    double sum = 0;
    for(int i=0; i<input.size(); i++){ sum = sum + input[i]; }
    double avg = sum/input.size();
    return avg;
}




