#include <iostream>
#include <string>
#include "Parser.h"
#include "DataPreprocessor.h"
#include "Operation.h"

using namespace std;

int main()
{
	string filename = "data/Classeur1.csv";
//	cin >> filename;
	Parser parser(filename);
	cout << endl;
//	parser.print();

	Mean mean;
	Median median;

	DataPreprocessor::SimpleImputer imputer(median);

	matrix data = parser.getData();

	imputer.fit(data);

	data = imputer.transform(data);

	column col;

	col = data.at(0);

	CalculateSum sum;
	matrix X;

	X.push_back(col);

	print(data);

	cout << sum.calculate(X);

	return 0;
}
