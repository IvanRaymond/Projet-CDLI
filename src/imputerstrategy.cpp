#include "imputerstrategy.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

ImputerStrategy::~ImputerStrategy() {}

ImputerMean::ImputerMean() {}

ImputerMean::ImputerMean(matrix X){
    data = X;
}

ImputerMean::~ImputerMean() {}

matrix ImputerMean::transform(matrix& X) {
    float sum = 0, ImputerMean = 0;
    bool nan;	// not a number

    for(int i = 0; i < X.size(); i++)
    {
        nan = false;
        // Start at 1 to avoid tag
        for(int j = 1; j < X[i].size(); j++)
        {
            string current = X.at(i).at(j);
            if(isFloat(current)) sum += stof(current);
            else if(current == "") {}	// empty string is not a float so skip it
            else nan = true;
        }
        if(!nan)
        {
            ImputerMean = sum/X.size()-1;
            // Start at 1 to avoid tag
            for(int j = 1; j < X[i].size(); j++)
            {
                string current = X.at(i).at(j);
                if(current == "")
                {
                    X.at(i).at(j) = to_string(ImputerMean);
                }
            }
        }
        else    // Non numerical columns case
        {
            for(int j = 1; j < X[i].size(); j++)
            {
                string current = X.at(i).at(j);
                if(current == "")
                {
                    X.at(i).at(j) = "missing value";
                }
            }
        }

    }
    return X;
}

ImputerMedian::ImputerMedian() {}

ImputerMedian::~ImputerMedian() {}

matrix ImputerMedian::transform(matrix &X) {
    bool nan;	// not a number
    float ImputerMedian;

    for(int i = 0; i < X.size(); i++)
    {
        nan = false;
        // Start at 1 to avoid tag
        for(int j = 1; j < X[i].size(); j++)
        {
            string current = X.at(i).at(j);
            if(!isFloat(current) && current != "") nan = true;
        }
        if(!nan)
        {
            vector<float> temp;
            // Start at 1 to avoid tag
            for(int k=1; k < X[i].size(); k++)
            {
                // Since sort only works on numerical vectors convert and add to a numerical vector
                if(isFloat(X[i][k])) temp.push_back(stof(X[i][k]));
            }
            // sort the numerical vector
            sort(temp.begin(),temp.end());
            ImputerMedian = temp.at(temp.size()/2);

            // Start at 1 to avoid tag
            for(int j = 1; j < X[i].size(); j++)
            {
                // Replace missing values with median of column
                string current = X.at(i).at(j);
                if(current == "") X.at(i).at(j) = to_string(ImputerMedian);
            }
        }
        else    // Non numerical columns case
        {
            // Start at 1 to avoid tag
            for(int j = 1; j < X[i].size(); j++)
            {
                string current = X.at(i).at(j);
                if(current == "") X.at(i).at(j) = "missing value";
            }
        }
    }
    return X;
}

bool isFloat(string myString) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
