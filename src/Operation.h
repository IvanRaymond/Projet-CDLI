/*
 * Operation.h
 *
 *  Created on: 25 Apr 2021
 *      Author: ivan
 */

#ifndef SRC_OPERATION_H_
#define SRC_OPERATION_H_

#include <string>
#include <vector>
#include <exception>

struct OperationError : public std::exception {
	const char * what () const throw ()
    {
    	return "Operation not permitted";
    }
};

using namespace std;

#define matrix vector<vector<string>>
#define column vector<string>

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

#endif /* SRC_OPERATION_H_ */
