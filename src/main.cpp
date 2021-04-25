#include <iostream>
#include "Parser.h"
#include "DataPreprocessor.h"

using namespace std;

int main()
{
	string filename = "data/Classeur1.csv";
//	cin >> filename;
	Parser parser(filename);
	cout << endl;
	parser.print();

	DataPreprocessor::SimpleImputer imputer(mean);

	matrix data = parser.getData();

	imputer.fit(data);

	data = imputer.transform(data);

	print(data);

	return 0;
}
