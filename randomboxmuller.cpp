/*
 * Implementation of the random number generator that uses the Marsaglia-Bray version
 *      of the Box-Muller algorithm to generate standard normal random numbers from
 *      a collection of uniform random numbers in (0,1).
 *
 * Yongyi Ye
 */

#include<deque>
#include<math.h>
#include<limits.h>

#include"randomboxmuller.hpp"

using namespace std;

RandomBoxMuller::RandomBoxMuller(int seed_):Random(seed_){}

RandomBoxMuller::RandomBoxMuller(const RandomBoxMuller& input):Random(input){}

RandomBoxMuller::~RandomBoxMuller(){}

RandomBoxMuller& RandomBoxMuller::operator= (const RandomBoxMuller& input){
    Random::operator=(input);
    return (*this);
}

/* the Marsaglia-Bray version of Box-Muller */
/* NEED TO MODIFY */
deque< deque<double> > RandomBoxMuller::get_normal(int N, int n){
    deque<double> uniform(Random::get_uniform());
    deque<double> container;

    //the uniform numbers get from the deque
    double u1;
    double u2;
    double x = INT_MAX;

    //index of the position in the uniform deque so far
    int index = 0;

    //start the looping until the uniform number deque is exhausted
    while(index+1 < uniform.size()){

        while(x>1 && (index+1)<uniform.size()){
            u1 = uniform[index];
            u2 = uniform[index+1];
            u1 = 2*u1 - 1;
            u2 = 2*u2 - 1;

            x = u1*u1 + u2*u2;
            index = index+2;
        }

        //make sure the last two numbers get from the loop are valid
        //if( (index+1)>=uniform.size() && x>1){ break; }
        if(x>1){ break; }

        double y = sqrt(-2 * (log(x)/x));

        double z1 = u1*y;
        double z2 = u2*y;

        container.push_back(z1);
        container.push_back(z2);

        //reset the value of x
        x = INT_MAX;
    }

    return container;
}

Random* RandomBoxMuller::clone() const{
    return new RandomBoxMuller(*this);
}
