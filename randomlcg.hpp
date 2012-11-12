/*
 * Declaration of the random number generator using linear congruential method
 *      to generate the underlying uniformly distributed numbers.
 *
 * Yongyi Ye
 */

#ifndef RANDOMLCG_HPP
#define RANDOMLCG_HPP

#include"random.hpp"

/* the linear congruential generator */
class Lcg{

    private:
        int seed;   //the initial seed of the generator
        int current;//the current seed to compute the next random number

    public:
        //constructor that takes in a seed_ number
        Lcg(double seed_);

        //get the next uniform number
        double get_uniform();

        //reset the generator so that the current seed is equal to the initial seed
        void reset();

        //set the seed of the generator
        void set_seed(double seed_);

        //skip a given number of numbers generated
        void skip(int number);
};

/* adapter to adapt the linear congruential generator to the random number generator interface */
class RandomLcg: public Random{

    private:
        Lcg inner;//the inner random number generator

    public:
        //constructor that takes in a seed_ number
        RandomLcg(double seed_);

        //get a uniformly distributed number in (0,1)
        virtual double get_uniform() ;

        //get a standard normally distributed number using inverse transformation method
        //      (Beasley-Springer-Moro method)
        virtual double get_normal();

        //reset the random number generator to initial state
        virtual void reset();

        //skip the given number of numbers generated
        virtual void skip(int number);

        //set the seed of the generator with a given seed_
        virtual void seed(int seed_);

        //returns a pointer to the copy of the generator itself (virtual copy construction)
        virtual Random* clone();

};

#endif
