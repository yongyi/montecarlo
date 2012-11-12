/*
 * Declarations of the payoffs of options of different types.
 *
 * Yongyi (Ivan) Ye
 */

#ifndef PAYOFFS_HPP
#define PAYOFFS_HPP

#include<string>
using std::string;

#include"statgatherer.hpp"

class Payoff{

    /* defining an interface */

    public:

        //overloaded operator that returns the payoff of an option by taking a statistics gatherer object
        virtual double operator()(StatGatherer gather) = 0;

        //function that returns a string description of the option
        virtual string to_string() const = 0;

        //a virtual copy constructor that returns a pointer to a copy of the option itself
        virtual Payoff* clone() const = 0;


};

class CallPayoff: public Payoff{

    private:
        double k;//strike price

    public:
        CallPayoff(double k_);

        double operator()(StatGatherer gather);
        string to_string() const;
        Payoff* clone() const;

};

class PutPayoff: public Payoff{

    private:
        double k;//strike price

    public:
        PutPayoff(double k_);

        double operator()(StatGatherer gather);
        string to_string() const;
        Payoff* clone() const;

};


#endif
