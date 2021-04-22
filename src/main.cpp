#include <iostream>
#include "Parser.h"

using namespace std;

int main()
{
	string filename = "data/Classeur1.csv";
//	cout << "Enter filename : ";
//	cin >> filename;
	Parser parser(filename);
	parser.print();

	return 0;
}
