/*
 * DataPreprocessor.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: ivan
 */

#include "DataPreprocessor.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

DataPreprocessor::DataPreprocessor(){}

DataPreprocessor::SimpleImputer::SimpleImputer(Strategy strat)
{
	strategy = strat;
}

DataPreprocessor::SimpleImputer::SimpleImputer(Strategy strat, string fill)
{
	strategy = strat;
	fill_value = fill;
}

void DataPreprocessor::SimpleImputer::fit(matrix mydata)
{
	data = mydata;
}

// Impute all missing data into X
matrix DataPreprocessor::SimpleImputer::transform(matrix &X)
{
	matrix process = data;

	return process;
}

DataPreprocessor::~DataPreprocessor() {}

bool isFloat(string myString) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
