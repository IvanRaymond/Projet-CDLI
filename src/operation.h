#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <vector>
#include <exception>

#define matrix vector<vector<string>>
#define column vector<string>

struct OperationError : public std::exception {
    const char * what () const throw ()
    {
        return "Operation not permitted";
    }
};

using namespace std;

class Operation {
public:
    virtual ~Operation();
    virtual string calculate(matrix X) = 0;
};

class CalculateSum : public Operation{
public:
    CalculateSum();
    virtual ~CalculateSum();
    virtual string calculate(matrix X);
};

class CalculateAverage : public Operation{
public:
    CalculateAverage();
    virtual ~CalculateAverage();
    virtual string calculate(matrix X);
};

class CalculateMedian : public Operation{
public:
    CalculateMedian();
    virtual ~CalculateMedian();
    virtual string calculate(matrix X);
};

class CalculateMax : public Operation{
public:
    CalculateMax();
    virtual ~CalculateMax();
    virtual string calculate(matrix X);
};

float getMedian(matrix X, int i, int start = 1);

#endif // OPERATION_H
