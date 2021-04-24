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

	// Replace with call to Qt to show Message Box
	// Or catch error and display
	if(!myFile.is_open()) throw runtime_error("Fichier introuvable");

	if(myFile.good())
	{
		getline(myFile, l);
		stringstream stream(l);
		while(getline(stream, c, ';'))
		{
			result.push_back(vector<string> {c});
		}
	}

	while(getline(myFile, l))
	{
		stringstream stream(l);
		cI = 0;

		while(stream >> val)
		{
			size_t pos = 0;
			string token;
			while ((pos = val.find(delimiter)) != string::npos)
			{
				token = val.substr(0, pos);
				result.at(cI).push_back(token);
				val.erase(0, pos + delimiter.length());
				cI++;
			}
			result.at(cI).push_back(val);
		}
	}
	data = result;

	myFile.close();
}

void Parser::print()
{
	matrix vect = data;
	int colSize = vect[0].size();
	for (int i = 0; i < colSize; i++)
	{
		for (int j = 0; j < vect.size(); j++)
		{
			colSize = vect[j].size();
			cout << "| " << vect[j][i] << " |";
		}

		cout << endl;
	}
}

void Parser::print(matrix X)
{
	matrix vect = X;
	int colSize = vect[0].size();
	for (int i = 0; i < colSize; i++)
	{
		for (int j = 0; j < vect.size(); j++)
		{
			colSize = vect[j].size();
			cout << "| " << vect[j][i] << " |";
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

