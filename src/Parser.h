/*
 * Parser.h
 *
 *  Created on: 22 Apr 2021
 *      Author: ivan
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define matrix vector<vector<string>>
#define column vector<string>

class Parser {

public:
	// Vecteur contenant les colonnes comme pair d'entete et vecteur contenant les valeurs
	matrix data;
	string delimiter = ";";
	string file;

	Parser();
	Parser(string fileName);

	void parse(string fileName);
	void setFile(string fileName);
	void print();
	void print(matrix data);
	void setEncoding(string encoding);
	matrix getData();

	virtual ~Parser();
};

#endif /* PARSER_H_ */

