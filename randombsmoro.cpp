/*
 * The random number generator that uses the Beasley-Springer-Moro Inverse
 *      Transformation Method to generate standard normal random numbers from
 *      a collection of uniform random numbers.
 *
 * Yongyi Ye
 */

#include<math.h>
#include<deque>

#include"randombsmoro.hpp"

using namespace std;

/* constants for use of the Beasley-Springer-Moro method */
const double a0 = 2.50662823884;
const double a1 = -18.61500062529;
const double a2 = 41.39119773534;
const double a3 = -25.44106049637;

const double b0 = -8.47351093090;
const double b1 = 23.08336743743;
const double b2 = -21.06224101826;
const double b3 = 3.13082909833;

const double c0 = 0.3374754822726147;
const double c1 = 0.9761690190917186;
const double c2 = 0.1607979714918209;
const double c3 = 0.0276438810333863;
const double c4 = 0.0038405729373609;
const double c5 = 0.0003951896511919;
const double c6 = 0.0000321767881768;
const double c7 = 0.0000002888167364;
const double c8 = 0.0000003960315187;

/* helper method */
double bsm(double u){
/*
 * the Beasley-Springer-Moro Inverse Transform Method
 *
 * input: u - a uniformly distributed number in (0,1)
 * output: the inverse transformed standard normal number
 */
    double y = u-0.5;
    double x;

    if(fabs(y) < 0.42){
        double r = y*y;
        x = y * (((a3*r + a2)*r + a1)*r + a0)/((((b3*r + b2)*r + b1)*r + b0)*r +1 );
    }
    else{
        double r = u;
        if(y>0){ r = 1-u; }

        r = log(-log(r));
        x = c0 + r*(c1 + r*(c2 + r*(c3 + r*(c4 + r*(c5 + r*(c6 + r*(c7 + r*c8)))))));

        if(y<0){ x = -x; }
    }
    return x;
}


/**** Beasley-Springer-Moro generator ****/
RandomBsmoro::RandomBsmoro(int step_, int seed_):Random(step_, seed_){}

RandomBsmoro::RandomBsmoro(const RandomBsmoro& input): Random(input){}

RandomBsmoro::~RandomBsmoro(){}

RandomBsmoro& RandomBsmoro::operator= (const RandomBsmoro& input){
    RandomBsmoro::operator=(input);
    return (*this);
}

//use beasley-springer-moro method to get a chain of standard normals
deque<double> RandomBsmoro::get_normal(){
    deque<double> container(Random::get_uniform());

    for(int i=0; i<container.size(); i++){
        //call the bsm method defined above
        container[i] = bsm(container[i]);
    }
    return container;
}

Random* RandomBsmoro::clone(){
    return new RandomBsmoro(*this);
}
