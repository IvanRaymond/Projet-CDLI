/*
 * DataPreprocessor.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: ivan
 * Description: Inspired by python Data preprocessing library. This class implements a simple imputer to replace
 *              missing values from a dataset. The replacement strategy is implemented in the class ImputerStrategy
 */

#include "datapreprocessor.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

DataPreprocessor::DataPreprocessor(){}
DataPreprocessor::~DataPreprocessor() {}

DataPreprocessor::SimpleImputer::SimpleImputer(ImputerStrategy &strat)
{
    strategy = & strat;
}

DataPreprocessor::SimpleImputer::SimpleImputer(ImputerStrategy &strat, string fill)
{
    strategy = & strat;
    fill_value = fill;
}

void DataPreprocessor::SimpleImputer::fit(matrix mydata)
{
    data = mydata;
}

// Input all missing data into X
matrix DataPreprocessor::SimpleImputer::transform(matrix &X)
{
    return strategy->transform(X);
}
