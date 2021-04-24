#include <iostream>
#include "Parser.h"
#include "DataPreprocessor.h"

using namespace std;

int main()
{
	string filename = "data/Classeur1.csv";
//	cout << "Enter filename : ";
//	cin >> filename;
	Parser parser(filename);
	cout << endl;
	parser.print();

	DataPreprocessor::SimpleImputer imputer(mean);

	imputer.fit(parser.getData());

	return 0;
}
