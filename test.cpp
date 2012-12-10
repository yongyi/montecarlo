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

#include"payoff.hpp"
#include"statgatherer.hpp"
#include"montecarlogeneral.hpp"
#include"montecarlovanilla.hpp"

using namespace std;

void print(const deque<double>& input){
    for(int i=0; i<input.size(); i++){
        cout << input[i] << "  ";
    }

    cout << endl << endl;
}

int main(){
    cout.precision(10);

    int seed = 1;

    RandomBsmoro bsm(seed);
    RandomBoxMuller box(seed);
    RandomAcceptReject ar(seed);

    //PutPayoff put(55);
    /*
    MonteCarloGeneral general_1(50, 0.3, 0.5, 0.04, 0, put, bsm);
    MonteCarloGeneral general_2(50, 0.3, 0.5, 0.04, 0, put, box);
    MonteCarloGeneral general_3(50, 0.3, 0.5, 0.04, 0, put, ar);
    cout << "bsm: " << general_1.price(5120000, 1) << endl;
    cout << "boxmuller" << general_2.price(5120000, 1) << endl;
    cout << "ar" << general_3.price(5120000, 1) << endl;
    */

    MonteCarloVanilla vanilla_1(50, 55, 0.3, 0.5, 0.04, 0, "put", bsm);
    MonteCarloVanilla vanilla_2(50, 55, 0.3, 0.5, 0.04, 0, "put", box);
    MonteCarloVanilla vanilla_3(50, 55, 0.3, 0.5, 0.04, 0, "put", ar);

    vanilla_1.run_monte_carlo(5120000);
    vanilla_2.run_monte_carlo(5120000);
    vanilla_3.run_monte_carlo(5120000);

    cout << "bsm " << vanilla_1.get_price() << endl;
    cout << "box " << vanilla_2.get_price() << endl;
    cout << "ar" << vanilla_3.get_price() << endl;

/*
    RandomBsmoro bsm(N, seed);
    RandomBoxMuller box(N, seed);
    RandomAcceptReject ar(N, seed);

    Antithetic anti(N,seed, ar);

    deque<double> holder;

    cout << "bsm" << endl;
    holder = bsm.get_normal(); print(holder);

    cout << "box" << endl;
    holder.clear();
    holder = box.get_normal(); print(holder);

    cout << "ar" << endl;
    holder.clear();
    holder = ar.get_normal(); print(holder);

    cout << "anti" << endl;
    holder.clear();
    holder = anti.get_normal(); print(holder);

    holder.clear();
    holder = anti.get_normal(); print(holder);
*/
    cout << "Hello World" << endl;

}
