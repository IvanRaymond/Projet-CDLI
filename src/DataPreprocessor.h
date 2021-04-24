/*
 * DataPreprocessor.h
 *
 *  Created on: 23 Apr 2021
 *      Author: ivan
 */

#ifndef SRC_DATAPREPROCESSOR_H_
#define SRC_DATAPREPROCESSOR_H_
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define matrix vector<vector<string>>
#define column vector<string>

enum Strategy { mean, median, constant };

class DataPreprocessor {
public:
	class SimpleImputer
	{
	public:
		Strategy strategy;
		string fill_value;
		matrix data;
		SimpleImputer(Strategy strategy);
		SimpleImputer(Strategy strategy, string fill_value);

		void fit(matrix data);
		matrix transform(matrix &data);
	};

	DataPreprocessor();

	virtual ~DataPreprocessor();
};

bool isFloat(string myString);

#endif /* SRC_DATAPREPROCESSOR_H_ */


