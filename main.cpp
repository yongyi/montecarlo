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
//#include"montecarlo.cpp"

using namespace std;

void print(const deque<double>& input){
    for(int i=0; i<input.size(); i++){
        cout << input[i] << "  ";
    }

    cout << endl << endl;
}

int main(){

    int seed = 1;
    int N = 10000 * pow(2,9);

    RandomBsmoro bsm(seed, N);
    RandomBoxMuller box(seed, N);
    RandomAcceptReject ar(seed, N);

    Antithetic anti(seed, N, ar);

    deque<double> holder;

    holder = bsm.get_normal();
    print(holder);

    holder = box.get_normal();
    print(holder);

    holder = ar.get_normal();
    print(holder);

    holder = anti.get_normal();
    print(holder);

    holder = anti.get_normal();
    print(holder);


}
