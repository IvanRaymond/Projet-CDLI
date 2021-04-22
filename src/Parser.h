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



class Parser {

public:
	// Vecteur contenant les colonnes comme pair d'entete et vecteur contenant les valeurs
	vector<vector<string>> data;
	string delimiter = ";";
	string file;

	Parser();
	Parser(string fileName);

	void parse(string fileName);
	void setFile(string fileName);
	void print();
	void setEncoding(string encoding);

	virtual ~Parser();
};

#endif /* PARSER_H_ */

