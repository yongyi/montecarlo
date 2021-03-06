/*
 * The declaration of the random number generator interface and the linear congruential
 *      generator to generate uniformly distributed numbers in (0,1) which is the uniform
 *      number generator by default.(The only uniform number generator that will be used
 *      in math9821.)
 *
 * Yongyi Ye
 */

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include<deque>
using namespace std;

/* the linear congruential generator */
class Lcg{

    private:
        int seed;   //the initial seed of the generator
        long current;//the current seed to compute the next random number

    public:
        //constructor that takes in a seed_ number
        Lcg(int seed_);

        //get the next uniform number
        double get_uniform();

        //reset the generator so that the current seed is equal to the initial seed
        void reset();

        //set the seed of the generator
        void set_seed(int seed_);

        //skip a given number of numbers generated
        void skip(int number);
};

/* the random number generator interface */
class Random{

    public:
        //constructor,  destructor, and assignment operator
        Random(int seed_);
        Random(const Random& input);
        virtual ~Random();
        virtual Random& operator= (const Random& input);

        //get a collection of N uniformly distributed numbers in (0,1)
        virtual deque<double> get_uniform(int N);

        //set the seed of the generator with a given seed_
        virtual void set_seed(int seed_);

        //reset the random number generator to initial state
        virtual void reset();

        //skip the given number of numbers generated
        virtual void skip(int number);

        //get a collection of standard normally distributed number for simulation
        //      need to get N uniformly distributed numbers from the get_uniform function
        virtual deque<double> get_normal(int N) = 0;

        //returns a pointer to the copy of the generator itself (virtual copy construction)
        virtual Random* clone() const = 0;

    private:
        Lcg inner; //the uniform number generator by default
};

#endif
