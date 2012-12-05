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

Antithetic::Antithetic(int seed_, const Random& inner_):Random(seed_),
                                                        inner(inner_),
                                                        use_antithetic(false){}

Antithetic::Antithetic(const Antithetic& input):Random(input),
                                                inner(input.inner),
                                                use_antithetic(input.use_antithetic){}

Antithetic::~Antithetic(){}

Antithetic& Antithetic::operator= (const Antithetic& input){
    Random::operator=(input);
    inner = input.inner;
    use_antithetic = input.use_antithetic;

    return (*this);
}

/* antithetic variance reduction technique */
/* NEED TO MODIFY */
deque<double> Antithetic::get_normal(int N){

    if(use_antithetic == false){
        //generate a collection of normal random numbers using the inner generator
        deque<double> container(inner->get_normal(N));

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
