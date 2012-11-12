/*
 * Declaration of statistics gatherer class that keeps record of the
 *      values and the max, min, mean of the values. Assuming the numbers
 *      are all positive.
 *
 * Yongyi (Ivan) Ye
 */

#ifndef STATGATHERER_HPP
#define STATGATHERER_HPP

#include<vector>
using namespace std;

class StatGatherer{

    private:
        double runningSum;  //the sum of the numbers stored in the gatherer so far
        double minVal;         //the min of the numbers stored in the gatherer so far
        double maxVal;         //the max of the numbers stored in the gatherer so far
        vector<double> data;//the container for the numbers

    public:
        StatGatherer();

        //function to dump a data number in the gatherer
        void dump_one_number(double number);

        //functions to get the max/min/mean/data/number of numbers so far
        double max() const;
        double min() const;
        double mean() const;
        int size() const;
        vector<double> result_so_far() const;

        //function to get the last number pushed in
        double get_last() const;

        //function to check if the gatherer is empty
        bool is_empty() const;

        //function to clear/reset the data stored in the gatherer
        void clear();


};

#endif
