
/*
 * Implementation of the random number generator that uses the Acceptance-Rejection
 *      method to generate standard normal random numbers from a collection of uniform
 *      random numbers in (0,1).
 *
 * Yongyi Ye
 */

#define _USE_MATH_DEFINES
#include<deque>
#include<math.h>
#include<limits.h>

#include"randomacceptreject.hpp"

using namespace std;

RandomAcceptReject::RandomAcceptReject(int seed_):Random(seed_){}

RandomAcceptReject::RandomAcceptReject(const RandomAcceptReject& input):Random(input){}

RandomAcceptReject::~RandomAcceptReject(){}

RandomAcceptReject& RandomAcceptReject::operator= (const RandomAcceptReject& input){
    Random::operator=(input);
    return (*this);
}

/* acceptance-rejection method */
/* NEED TO MODIFY */
deque< deque<double> > RandomAcceptReject::get_normal(int N, int n){
    deque<double> uniform(Random::get_uniform());
    deque<double> container;

    //the uniform number get from the deque
    double u1;
    double u2 = INT_MAX;
    double u3;
    double x = 0;

    //index of the current position in the uniform deque so far
    int index = 0;

    while(index+2 < uniform.size()){

        while(u2>exp(-0.5*(x-1)*(x-1)) && (index+2)<uniform.size()){
            u1 = uniform[index];
            u2 = uniform[index+1];
            u3 = uniform[index+2];

            x = -log(u1);
            index = index + 3;
        }

        //make sure the last numbers get from the loop are valid
        //if((index+2)>=uniform.size() && u2>exp(-0.5*(x-1)*(x-1))){ break; }
        if( u2 > exp(-0.5*(x-1)*(x-1))){ break; }

        if(u3 <= 0.5){ x = -x; }
        container.push_back(x);

        //reset the value of x
        u2 = INT_MAX;
    }

    return container;
}

Random* RandomAcceptReject::clone() const{
    return new RandomAcceptReject(*this);
}
