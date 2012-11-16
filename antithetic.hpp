/*
 * Random number generator that generates a collection of standard normal random numbers
 *      using the antithetic variance reduction technique by decorating the random number
 *      generator class.
 *
 * Yongyi Ye
 */

#ifndef ANTITHETIC_HPP
#define ANTITHETIC_HPP

#include<deque>

#include"random.hpp"
#include"wrapper.hpp"

using namespace std;

class Antithetic: public Random{

    public:
        //constructor, destructor, assignment operator
        Antithetic(int step_, int seed_, const Random& inner_);
        Antithetic(const Antithetic& input);
        virtual ~Antithetic();
        virtual Antithetic& operator= (const Antithetic& input);

   /*
     *  no need to override the following functions - use the base class one

        *get a collection of uniformly distributed number in (0,1)
        virtual deque<double> get_uniform();

        *set the seed of the generator with a given seed_
        virtual void set_seed(int seed_);

        *reset the random number generator to initial state
        virtual void reset();

        *skip the given number of numbers generated
        virtual void skip(int number);
     *
     */

        //get a collection of standard normally distributed number
        virtual deque<double> get_normal();

        //returns a pointer to the copy of the generator itself (virtual copy construction)
        virtual Random* clone() const;

    private:
        Wrapper<Random> inner;      //the inner standard normal random number generator
        deque<double> antithetic;   //the collection of antithetic variables
        bool use_antithetic;        //boolean indicating whether to use antithetic variables or not
};

#endif