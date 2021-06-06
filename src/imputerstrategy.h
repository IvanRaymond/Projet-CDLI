#ifndef ImputerStrategy_H
#define ImputerStrategy_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define matrix vector<vector<string>>
#define column vector<string>

//Interface ImputerStrategy
class ImputerStrategy {
    public:
        virtual ~ImputerStrategy();
        virtual matrix transform(matrix& X) = 0;
};

class ImputerMean : public ImputerStrategy {
    public:
        matrix data;
        ImputerMean();
        ImputerMean(matrix X);
        virtual ~ImputerMean();
        virtual matrix transform(matrix& X);
};

class ImputerMedian : public ImputerStrategy {
    public:
        ImputerMedian();
        ImputerMedian(matrix &X);
        virtual ~ImputerMedian();
        virtual matrix transform(matrix& X);
};

bool isFloat(string myString);

#endif // ImputerStrategy_H
