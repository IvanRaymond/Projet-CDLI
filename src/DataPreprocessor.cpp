/*
 * DataPreprocessor.cpp
 *
 *  Created on: 23 Apr 2021
 *      Author: ivan
 */

#include "DataPreprocessor.h"
#include <iostream>
#include <vector>
#include <algorithm>
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
	switch(strategy)
	{
		case Strategy::mean: return mean(X);
		case Strategy::median: return median(X);
	}
	return X;
}

matrix DataPreprocessor::SimpleImputer::mean(matrix &X)
{
	matrix process = data;
	float sum = 0, mean = 0;
	bool nan;	// not a number

	for(int i = 0; i < process.size(); i++)	// Index 0 is for tag
	{
		nan = false;
		for(int j = 1; j < process[i].size(); j++)
		{
			string current = process.at(i).at(j);
			if(isFloat(current)) sum += stof(current);
			else if(current == "") {}	// empty string is not a float
			else nan = true;
		}
		if(!nan)
		{
			mean = sum/process.size()-1;
			for(int j = 1; j < process[i].size(); j++)
			{
				string current = process.at(i).at(j);
				if(current == "")
				{
					process.at(i).at(j) = to_string(mean);
				}
			}
		}
		else
		{
			for(int j = 1; j < process[i].size(); j++)
			{
				string current = process.at(i).at(j);
				if(current == "")
				{
					process.at(i).at(j) = "missing value";
				}
			}
		}

	}

	X = process;
	return process;
}

matrix DataPreprocessor::SimpleImputer::median(matrix &X)
{
	matrix process = data;
	bool nan;	// not a number
	float median;

	for(int i = 0; i < process.size(); i++)	// Index 0 is for tag
	{
		nan = false;
		for(int j = 1; j < process[i].size(); j++)
		{
			string current = process.at(i).at(j);
			if(!isFloat(current) && current != "") nan = true;
		}
		if(!nan)
		{
			vector<float> temp;
			for(int k=1; k < process[i].size(); k++)
			{
				if(isFloat(process[i][k])) temp.push_back(stof(process[i][k]));
			}
			sort(temp.begin(),temp.end());
			median = temp.at(temp.size()/2);

			for(int j = 1; j < process[i].size(); j++)
			{
				string current = process.at(i).at(j);
				if(current == "") process.at(i).at(j) = to_string(median);
			}
		}
		else
		{
			for(int j = 1; j < process[i].size(); j++)
			{
				string current = process.at(i).at(j);
				if(current == "") process.at(i).at(j) = "missing value";
			}
		}
	}
	X = process;
	return process;
}

DataPreprocessor::~DataPreprocessor() {}

//Todo make function detect comma and decimal
bool isFloat(string myString) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
