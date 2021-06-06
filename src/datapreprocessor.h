#ifndef DATAPREPROCESSOR_H
#define DATAPREPROCESSOR_H

#include "imputerstrategy.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DataPreprocessor {
public:
    class SimpleImputer
    {
    public:
        ImputerStrategy* strategy;
        string fill_value;
        matrix data;
        SimpleImputer(ImputerStrategy &strategy);
        SimpleImputer(ImputerStrategy &strategy, string fill_value);

        void fit(matrix data);
        matrix transform(matrix &data);
    };

    DataPreprocessor();
    virtual ~DataPreprocessor();
};

#endif // DATAPREPROCESSOR_H
