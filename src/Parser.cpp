/*
 * Parser.cpp
 *
 *  Created on: 22 Apr 2021
 *      Author: ivan
 */

#include "Parser.h"
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>
using namespace std;

Parser::Parser(){}

Parser::Parser(string fileName)
{
	parse(fileName);
}


void Parser::parse(string fileName)
{
	string l, c, val;
	int cI;
	ifstream myFile(fileName);
	matrix result;
	column temp = column {};

	// Replace with call to Qt to show Message Box
	// Or catch error and display
	if(!myFile.is_open()) throw runtime_error("Fichier introuvable");

	if(myFile.good())
	{
		getline(myFile, l);
		stringstream stream(l);
		while(getline(stream, c, ';'))
		{
			temp.push_back(c);
		}
		result.push_back(temp);
	}

	cI = 1; // Index de la colonne courante

	while(getline(myFile, l))
	{
		stringstream stream(l);
		temp = column {};

		while(stream >> val)
		{
			size_t pos = 0;
			string token;
			while ((pos = val.find(delimiter)) != string::npos)
			{
			    token = val.substr(0, pos);
			    temp.push_back(token);
			    val.erase(0, pos + delimiter.length());
			}
			temp.push_back(val);
			result.push_back(temp);
		}
	}
	data = result;

	myFile.close();
}

void Parser::print()
{
	matrix vect = data;
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); j++)
		{
			cout << vect[i][j] << " ";
		}
		cout << endl;
	}
}

void Parser::setFile(string fileName)
{
	file = fileName;
}

void Parser::setEncoding(string encoding)
{
	delimiter = encoding;
}

matrix Parser::getData()
{
	return data;
}

Parser::~Parser() {}

