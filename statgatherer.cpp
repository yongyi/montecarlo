/*
 * implementation of the statistics gatherer class
 */

#include<deque>
#include<limits.h>
#include"statgatherer.hpp"

using namespace std;

/* constructor */
StatGatherer::StatGatherer():runningSum(0),
                             data(deque<double>()){}

void StatGatherer::dump_one_number(double number){

    //update running sum
    runningSum = runningSum + number;

    //dump the number
    data.push_back(number);

}

/* get the statistics gathered so far */
double StatGatherer::mean() const{
    return runningSum/data.size();
}

int StatGatherer::size() const{
    return data.size();
}

deque<double> StatGatherer::result_so_far() const{
    return data;
}


/* check if the gatherer is empty */
bool StatGatherer::is_empty() const{
    return data.empty();
}

/* reset the gatherer */
void StatGatherer::clear(){
    data.clear();
    runningSum = 0;
}



