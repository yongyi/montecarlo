/*
 * implementation of the statistics gatherer class
 */

#include<vector>
#include<limits.h>
#include"statgatherer.hpp"

using namespace std;

/* constructor */
StatGatherer::StatGatherer():runningSum(0),
                             minVal(INT_MAX),
                             maxVal(INT_MIN),
                             data(vector<double>()){}

void StatGatherer::dump_one_number(double number){

    //set the min and max by doing comparison
    if(number < minVal){ minVal = number; }
    if(number > maxVal){ maxVal = number; }

    //update running sum
    runningSum = runningSum + number;

    //dump the number
    data.push_back(number);

}

/* get the statistics gathered so far */
double StatGatherer::min() const{
    return minVal;
}

double StatGatherer::max() const{
    return maxVal;
}

double StatGatherer::mean() const{
    return runningSum/data.size();
}

int StatGatherer::size() const{
    return data.size();
}

vector<double> StatGatherer::result_so_far() const{
    return data;
}

/* get the last number pushed in */
double StatGatherer::get_last() const{
    //if the gatherer is empty, return an error number
    if(this->is_empty()){ return INT_MAX; }

    return data[data.size()-1];
}

/* check if the gatherer is empty */
bool StatGatherer::is_empty() const{
    return data.empty();
}

/* reset the gatherer */
void StatGatherer::clear(){
    data.clear();
    minVal = INT_MAX;
    maxVal = INT_MIN;
    runningSum = 0;
}



