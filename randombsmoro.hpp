/*
 * The random number generator that inherits from the random base class and
 *      uses the Beasley-Springer-Moro Inverse Transformation Method to
 *      generate standard normal random numbers from a collection of uniform
 *      random numbers in (0,1).
 *
 * Yongyi Ye
 */

#ifndef RANDOMBSMORO_HPP
#define RANDOMBSMORO_HPP

#include"random.hpp"

class RandomBsmoro: public Random{

    public:
        //constructor, destructor, assignment operator
        RandomBsmoro(int seed_);
        RandomBsmoro(const RandomBsmoro& input);
        virtual ~RandomBsmoro();
        virtual RandomBsmoro& operator= (const RandomBsmoro& input);

    /*
     *  no need to override the following functions - use the base class one

        *get a collection of N uniformly distributed numbers in (0,1)
        virtual deque<double> get_uniform(int N);

        *set the seed of the generator with a given seed_
        virtual void set_seed(int seed_);

        *reset the random number generator to initial state
        virtual void reset();

        *skip the given number of numbers generated
        virtual void skip(int number);

     *
     */

        //get a collection of standard normally distributed numbers for simulation
        //      N uniforms needed for generating n simulations using normals
        virtual deque<double> get_normal(int N);

        //returns a pointer to the copy of the generator itself (virtual copy construction)
        virtual Random* clone() const;

    private:
        /* no additional data members needed */

};

#endif
