/*
 * ImputerStrategy.h
 *
 *  Created on: 12 May 2021
 *      Author: ivan
 */

#ifndef SRC_IMPUTERSTRATEGY_H_
#define SRC_IMPUTERSTRATEGY_H_
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

class Mean : public ImputerStrategy {
	public:
		matrix data;
		Mean();
		Mean(matrix X);
		virtual ~Mean();
		virtual matrix transform(matrix& X);
};

class Median : public ImputerStrategy {
	public:
		Median();
		Median(matrix &X);
		virtual ~Median();
		virtual matrix transform(matrix& X);
};

bool isFloat(string myString);

#endif /* SRC_IMPUTERSTRATEGY_H_ */
