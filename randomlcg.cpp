/*
 * implementation of the random number generator using linear congruential generator
 *      to generate the underlying random uniform numbers
 *
 * Yongyi Ye
 */

#include<stdlib.h>
#include<math.h>

#include"randomlcg.hpp"

using namespace std;

/* outline of the linear congruential method
 *
 * x_(i+1) = (a*x_i + c) mod m
 * u_(i+1) = x_(i+1)/m
 *
 * return u_(i+1)
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



/* the random lcg adapter class */
//constructor
RandomLcg::RandomLcg(double seed_):inner(seed_){}

//get a uniformly distributed number
double RandomLcg::get_uniform(){
    return inner.get_uniform();
}

//get a standard randomly distributed number
double RandomLcg::get_normal(){
    //no change, call the base class function
    return Random::get_normal();
}

//reset the generator to initial state
void RandomLcg::reset(){
    inner.reset();
}

//skip the given number of numbers generated
void RandomLcg::skip(int number){
    inner.skip(number);
}

//set the seed of the generator
void RandomLcg::seed(int seed_){
    inner.set_seed(seed_);
}

//virtual copy construction that returns a copy of the generator itself on heap
Random* RandomLcg::clone(){
    return new RandomLcg(*this);
}

