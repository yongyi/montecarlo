/*
 * The declaration of the random number generator interface
 *
 * Yongyi Ye
 */

#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random{

    public:
        //get a uniformly distributed number in (0,1)
        virtual double get_uniform() = 0;

        //get a standard normally distributed number using inverse transformation method
        //      (Beasley-Springer-Moro method)
        virtual double get_normal();

        //reset the random number generator to initial state
        virtual void reset() = 0;

        //skip the given number of numbers generated
        virtual void skip(int number) = 0;

        //set the seed of the generator with a given seed_
        virtual void seed(int seed_) = 0;

        //returns a pointer to the copy of the generator itself (virtual copy construction)
        virtual Random* clone() = 0;

};

#endif
