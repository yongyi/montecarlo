/*
 * implementation of the random number generator base class and linear congruential
 *      uniform random number generator.
 *
 * Yongyi Ye
 */

#include<stdlib.h>
#include<math.h>

#include"random.hpp"

using namespace std;

/* outline of the linear congruential method
 *
 * x_(i+1) = (a*x_i + c) mod m
 * u_(i+1) = x_(i+1)/m
 *
 * return u_(i+1)
 *
 */


/* the constants used in the linear congruential method */
const int a = 39373;
const int c = 0;
const long  m = pow(2, 31) - 1;
const double reciprocal = 1.0/static_cast<double>(m);

/* linear congruential generator */
//constructor
Lcg::Lcg(double seed_):seed(seed_), current(seed_){}

//get the next uniformly distributed number
double Lcg::get_uniform(){
    current = (a*current + c) % m;
    return (current * reciprocal);
}

//reset the generator
void Lcg::reset(){
    current = seed;
}

//set the seed of the generator
void Lcg::set_seed(double seed_){
    seed = seed_;
    current = seed_;
}

//skip a given number of uniform numbers generated
void Lcg::skip(int number){
    for(int i=0; i<number; i++){
        get_uniform();
    }
}


/* the random base class */
Random::Random(int step_, int seed_):step(step_), inner(seed_){}

Random::Random(const Random& input):step(input.step), inner(input.inner){}

Random::~Random(){}

Random& Random::operator= (const Random& input){
    step = input.step;
    inner = input.inner;
    return (*this);
}

//get a collection of uniform random numbers in (0,1)
deque<double> Random::get_uniform(){
    deque<double> container;
    for(int i=0; i<step; i++){
        container.push_back(inner.get_uniform());
    }
    return container;
}

//set seed of the inner generator
void Random::set_seed(int seed_){
    inner.set_seed(seed_);
}

//reset the inner generator
void Random::reset(){
    inner.reset();
}

//skip a given number of random numbers generated
void Random::skip(int number){
    inner.skip(number);
}

