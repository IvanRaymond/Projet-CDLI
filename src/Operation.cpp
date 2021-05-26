/*
 * Operation.cpp
 *
 *  Created on: 25 Apr 2021
 *      Author: ivan
 */

#include "Operation.h"
#include "ImputerStrategy.h"
#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>


using namespace std;

Operation::~Operation() {}


CalculateSum::CalculateSum(){}
CalculateSum::~CalculateSum(){}

/*
 * Calculate the Sum of a Column if a single column is set
 * If multiple columns are set then will calculate the sum
 * of a line.
 */
string CalculateSum::calculate(matrix X){

	column col;
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

CalculateAverage::CalculateAverage(){}
CalculateAverage::~CalculateAverage(){}

string CalculateAverage::calculate(matrix X){

	column col;
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

CalculateMedian::CalculateMedian(){}
CalculateMedian::~CalculateMedian(){}

/*
 * Operation on row not permitted
 */
string CalculateMedian::calculate(matrix X){
	// Column case
	if (X.size() < 2) {
		return to_string(getMedian(X, 0, 0));
	} else {
		throw invalid_argument("Operation on multiple columns not allowed.");
	}
}

CalculateMax::CalculateMax(){}
CalculateMax::~CalculateMax(){}

/*
 * Return the max value in a matrix
 */
string CalculateMax::calculate(matrix X){

	column col;
	vector<double> colInt;
	double newMax, max;
	max = -std::numeric_limits<double>::max();

	for(string elem:col){
		colInt.push_back(stod(elem));
	}

	for (int i = 0; i < X.size(); i++){
		col = X.at(i);
		newMax = *max_element(colInt.begin(), colInt.end());
		max = (newMax > max) ? newMax : max;
	}
	return to_string(max);
}

