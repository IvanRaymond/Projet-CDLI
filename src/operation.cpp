/*
 * Operation.cpp
 *
 *  Created on: 25 Apr 2021
 *      Author: ivan
 * Description: Interface defining the operations on the dataset.
 */

#include "operation.h"
#include "imputerstrategy.h"

#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>


using namespace std;

Operation::~Operation() {}

/*
 * Calculate the Sum of a Column if a single column is set
 * If multiple columns are set then will calculate the sum
 * of a line.
 */
CalculateSum::CalculateSum(){}
CalculateSum::~CalculateSum(){}
string CalculateSum::calculate(matrix X){

    dataColumn col;
    double sum;

    // Column case
    if (X.size() < 2) {
        col = X.at(0);
        for(int i = 0; i< col.size(); i++){
            sum += stod(col.at(i));
        }
    }
    // Row case
    else {
        /*
         * The matrix contains a row so
         * every column has only one element
         */
        for(int i = 0; i < X.size(); i++){
            sum += stod(col.at(0));
        }
    }
    return to_string(sum);
}

/*
 * Calculate Average of a column or a row.
 */
CalculateAverage::CalculateAverage(){}
CalculateAverage::~CalculateAverage(){}
string CalculateAverage::calculate(matrix X){

    dataColumn col;
    double average, sum;
    CalculateSum calSum;

    sum = stod(calSum.calculate(X));

    // Column case
    if (X.size() < 2) {
        col = X.at(0);
        average = sum / (col.size());
    }
    // Row case
    else {
        average = sum / (X.size());
    }
    return to_string(average);
}

/*
 * Calculate median of a column
 */
CalculateMedian::CalculateMedian(){}
CalculateMedian::~CalculateMedian(){}
string CalculateMedian::calculate(matrix X){
    // Column case
    if (X.size() < 2) {
        return to_string(getMedian(X, 0, 0));
    } else {
        throw invalid_argument("Operation on multiple columns not allowed.");
    }
}

/*
 * Calculate the max of a matrix
 */
CalculateMax::CalculateMax(){}
CalculateMax::~CalculateMax(){}
string CalculateMax::calculate(matrix X){

    dataColumn col;
    vector<double> colInt;
    double max;
    // Initialising max as minimum value possible
    max = -std::numeric_limits<double>::max();

    // Add all numerical values to an array
    for(vector<string> elemVect:X){
        for(string elem:elemVect){
            if(isFloat(elem))
                colInt.push_back(stod(elem));
        }
    }
    // Function to get max element of numerical vector
    max = *max_element(colInt.begin(), colInt.end());

    return to_string(max);
}

/*
 * Takes a matrix and the index of the column
 * Return ImputerMedian or -1 if non numerical
 */
float getMedian(matrix X, int i, int start){
    bool nan;	// not a number
    float median = -1;

    nan = false;
    for(int j = start; j < X[i].size(); j++) {	// Checks if column is numerical
        string current = X.at(i).at(j);
        if(!isFloat(current) && current != "") nan = true;
    }
    if(!nan) {		// Case numerical
        vector<float> temp;
        for(int k = start; k < X[i].size(); k++) {
            // Creates a float vector containing all numerical values of the column
            // Sort doesn't work on strings so conversion is needed
            if(isFloat(X[i][k])) temp.push_back(stof(X[i][k]));
        }
        sort(temp.begin(),temp.end());
        median = temp.at(temp.size()/2);	//ImputerMedian is at the middle of the list
    }
    return median;
}
