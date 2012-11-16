/*
 * Implementation of the random number generator using the antithetic variance
 *      reduction technique.
 *
 * Yongyi Ye
 */

#include<deque>
#include<math.h>

#include"antithetic.hpp"

using namespace std;

Antithetic::Antithetic(int step_, int seed_, const Random& inner_):Random(step_, seed_),
                                                                  inner(inner_),
                                                                  antithetic(deque<double>()),
                                                                  use_antithetic(false){}

Antithetic::Antithetic(const Antithetic& input):Random(input),
                                                inner(input.inner),
                                                antithetic(input.antithetic),
                                                use_antithetic(input.use_antithetic){}

Antithetic::~Antithetic(){}

Antithetic& Antithetic::operator= (const Antithetic& input){
    Random::operator=(input);
    inner = input.inner;
    antithetic = input.antithetic;
    use_antithetic = input.use_antithetic;

    return (*this);
}

/* antithetic variance reduction technique */
deque<double> Antithetic::get_normal(){

    if(use_antithetic == false){
        //generate a collection of normal random numbers using the inner generator
        deque<double> container(inner->get_normal());

        //put the antithetic values in the antithetic deque
        for(int i=0; i<container.size(); i++){ antithetic.push_back(-container[i]); }
        use_antithetic = true;

        return container;
    }
    else{
        //use antithetic
        use_antithetic = false;
        return antithetic;
    }
}

Random* Antithetic::clone() const{
    return new Antithetic(*this);
}
