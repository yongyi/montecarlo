/*
 * Implementation of the general Monte-Carlo simulation option pricer.
 *
 * Yongyi Ye
 */

#include<stdlib.h>
#include<assert.h>
#include<deque>
#include<math.h>
#include<string>

#include"random.hpp"
#include"statgatherer.hpp"
#include"payoff.hpp"
#include"wrapper.hpp"
#include"montecarlogeneral.hpp"

using namespace std;

MonteCarloGeneral::MonteCarloGeneral(double s_, double vol_, double t_, double r_, double q_,
                                        const Payoff &option_, const Random &generator_, bool use_antithetic_):
                            s(s_), vol(vol_), t(t_), r(r_), q(q_), option(option_), generator(generator_), use_antithetic(use_antithetic_){}


/* monte-carlo simulation pricer */
double MonteCarloGeneral::price(int N, int m){

    // the delta_t that should be used in the simulation - dt = t for vanilla options
    double dt = t/static_cast<double>(m);
    //risk-free discount factor
    double discount = exp(-r*t);

    // the data containers
    StatGatherer gather;    //statistics gatherer
    deque<double> normal(generator->get_normal(N));   //store the normal random numbers generated
    deque<double> stockval; //store the intermediate stock values in one simulation

    // partition the normal random numbers
    int n = normal.size()/m;
    deque< deque<double> > grid(preprocess(n, m, normal));

    if(use_antithetic){ n = 2*n; }

    for(int i=0; i<n; i++){

        //get the simulated stock prices in one pass - the loop will not run if the time step is 1 (m==1)
        double s_stepwise = s * exp( (r-q-vol*vol/2.0)*dt + vol*sqrt(dt)*grid[i][0]);
        for(int j=1; j<m; j++){
            stockval.push_back(s_stepwise);
            s_stepwise = s_stepwise * exp( (r-q-vol*vol/2.0)*dt + vol*sqrt(dt)*grid[i][j]);
        }
        stockval.push_back(s_stepwise);
        gather.dump_one_number(option->payoff(stockval));

        //clear data, do another pass
        stockval.clear();
    }

    return discount * gather.mean();
}

/* reset the random number generator */
void MonteCarloGeneral::reset_generator(){
    generator->reset();
}

/* partition the random normals into n * m matrix of normals */
deque< deque<double> > MonteCarloGeneral::preprocess(int n, int m, const deque<double> &input){

    deque< deque<double> > result;

    for(int i=0; i<n; i++){
        deque<double> to_be_pushed;
        for(int j=0; j<m; j++){
            to_be_pushed.push_back(input[i*m + j]);
        }
        result.push_back(to_be_pushed);
    }

    // antithetic method
    if(use_antithetic){
        for(int i=0; i<n; i++){
            deque<double> to_be_pushed;
            for(int j=0; j<m; j++){ to_be_pushed.push_back(-result[i][j]);}
        result.push_back(to_be_pushed);
        }
    }

    return result;
}
