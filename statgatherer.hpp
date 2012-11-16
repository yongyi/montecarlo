/*
 * Declaration of statistics gatherer class that keeps record of the
 *      values and mean of the values. Assuming the numbers
 *      are all positive.
 *
 * Yongyi (Ivan) Ye
 */

#ifndef STATGATHERER_HPP
#define STATGATHERER_HPP

#include<deque>
using namespace std;

class StatGatherer{

    private:
        double runningSum;  //the sum of the numbers stored in the gatherer so far
        deque<double> data;//the container for the numbers

    public:
        StatGatherer();

        //function to dump a data number in the gatherer
        void dump_one_number(double number);

        double mean() const;
        int size() const;
        deque<double> result_so_far() const;

        //function to check if the gatherer is empty
        bool is_empty() const;

        //function to clear/reset the data stored in the gatherer
        void clear();


};

#endif
