/*
 * implementation of the payoff classes
 */

#include<string>
#include<sstream>
#include<algorithm>

#include"statgatherer.hpp"
#include"payoff.hpp"

using namespace std;

/* Call Payoff */
CallPayoff::CallPayoff(double k_):k(k_){}

double CallPayoff::operator()(StatGatherer gather){
    return max<double>(gather.get_last()-k, 0);
}

string CallPayoff::to_string() const{
    stringstream s;
    s << "European call option with strike " << k << " dollars" << endl;
    return s.str();
}

Payoff* CallPayoff::clone() const{
    return new CallPayoff(*this);
}


/* Put Payoff */
PutPayoff::PutPayoff(double k_):k(k){}

double PutPayoff::operator()(StatGatherer gather){
    return max<double>(k-gather.get_last(), 0);
}

string PutPayoff::to_string() const{
    stringstream s;
    s << "European put option with strike " << k << " dollars" << endl;
    return s.str();
}

Payoff* PutPayoff::clone() const{
    return new PutPayoff(*this);
}






