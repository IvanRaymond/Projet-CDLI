/*
 * DataPreprocessor.h
 *
 *  Created on: 23 Apr 2021
 *      Author: ivan
 */

#ifndef SRC_DATAPREPROCESSOR_H_
#define SRC_DATAPREPROCESSOR_H_
#include "ImputerStrategy.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define matrix vector<vector<string>>
#define column vector<string>

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

#endif /* SRC_DATAPREPROCESSOR_H_ */


