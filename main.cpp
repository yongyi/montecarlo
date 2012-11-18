/*
 * the main/test file to run monte-carlo simulation for pricing options
 *
 * Yongyi Ye
 */

#include<iostream>
#include<string>
#include<deque>
#include<math.h>

#include"random.hpp"
#include"randomacceptreject.hpp"
#include"randomboxmuller.hpp"
#include"randombsmoro.hpp"
#include"antithetic.hpp"

#include"payoff.hpp"
#include"statgatherer.hpp"
#include"montecarlo.hpp"

using namespace std;

void print(const deque<double>& input){
    for(int i=0; i<input.size(); i++){
        cout << input[i] << "  ";
    }

    cout << endl << endl;
}

int main(){

    int seed = 1;
    //int N = 10000 * pow(2,9);
    int N = 10;

    RandomBsmoro bsm(N, seed);
    RandomBoxMuller box(N, seed);
    RandomAcceptReject ar(N, seed);

    Antithetic anti(N,seed, ar);

    deque<double> holder;

    cout << "bsm" << endl;
    holder = bsm.get_normal();
    print(holder);

    cout << "box" << endl;
    holder.clear();
    holder = box.get_normal();
    print(holder);

    cout << "ar" << endl;
    holder.clear();
    holder = ar.get_normal();
    print(holder);

    cout << "anti" << endl;
    holder.clear();
    holder = anti.get_normal();
    print(holder);

    holder.clear();
    holder = anti.get_normal();
    print(holder);


    /* demonstration of use of monte-carlo */
    double s1 = 50;
    double vol1 = 0.2;
    double t1 = 0.5;
    double r1 = 0.05;
    double q1 = 0.03;
    long n = 1000000;
    CallPayoff call(50);
    RandomBsmoro gen(1, 1);
    bool use_control_variate = false;
    bool use_moment_matching = true;
    double price = monte_carlo(s1, vol1, t1, r1, q1, n, call, gen, use_control_variate, use_moment_matching);
    cout << "price: " << price << endl;

}
