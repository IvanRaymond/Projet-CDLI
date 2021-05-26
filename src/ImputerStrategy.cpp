/*
 * ImputerStrategy.cpp
 *
 *  Created on: 12 May 2021
 *      Author: ivan
 */

#include "ImputerStrategy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

ImputerStrategy::~ImputerStrategy() {}

Mean::Mean() {}

Mean::Mean(matrix &X){
	data = X;
}

Mean::~Mean() {}

/*
 * Mean strategy checks column for numerical value content and if true
 * replaces missing values by the mean of the column.
 * In case of non numerical values, "missing value" replaces the empty
 * string.
 */
matrix Mean::transform(matrix& X) {
	float sum = 0, mean = 0;
	bool nan;	// not a number

	for(int i = 0; i < X.size(); i++)	// Index 0 is for tag
	{
		nan = false;
		for(int j = 1; j < X[i].size(); j++) {		//Checks if column is numerical
			string current = X.at(i).at(j);
			if(isFloat(current)) sum += stof(current);
			else if(current == "") {}	// empty string is not a float
			else nan = true;
		}
		if(!nan) {
			mean = sum/X.size()-1;
			for(int j = 1; j < X[i].size(); j++) {
				string current = X.at(i).at(j);
				if(current == "") {
					X.at(i).at(j) = to_string(mean);	//Case numerical
				}
			}
		}
		else {
			for(int j = 1; j < X[i].size(); j++) {	//Case non numerical
				string current = X.at(i).at(j);
				if(current == "") {
					X.at(i).at(j) = "missing value";
				}
			}
		}

	}

	cout << "Mean executed" << endl;

	return X;
}

Median::Median() {}

Median::Median(matrix &X) {
	data = X;
}

Median::~Median() {}

/*
 * Median strategy checks column for numerical value content and if true
 * replaces missing values by the median of the column.
 * In case of non numerical values, "missing value" replaces the empty
 * string.
 */
matrix Median::transform(matrix &X) {
	bool nan;	// not a number
	float median;

	for(int i = 0; i < X.size(); i++)	// Index 0 is for tag
	{
		median = getMedian(X, i);

		if(median != -1) {		// Case numerical
			for(int j = 1; j < X[i].size(); j++) {
				string current = X.at(i).at(j);
				if(current == "") X.at(i).at(j) = to_string(median);
			}
		}
		else {		// Case non numerical
			for(int j = 1; j < X[i].size(); j++) {
				string current = X.at(i).at(j);
				if(current == "") X.at(i).at(j) = "missing value";
			}
		}
	}

	cout << "median executed" << endl;

	return X;
}

/*
 * Takes a matrix and the index of the column
 * Return median or -1 if non numerical
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
		median = temp.at(temp.size()/2);	//Median is at the middle of the list
	}
	return median;
}

bool isFloat(string myString) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
