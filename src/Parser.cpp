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

Parser::Parser(string fileName)
{
	parse(fileName);
}


void Parser::parse(string fileName)
{
	string l, c, val;
	int cI;
	ifstream myFile(fileName);
	vector<vector<string>> result;

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
		cI = 0; // Index de la colonne courante

		while(stream >> val)
		{
			size_t pos = 0;
			string token;
			while ((pos = val.find(delimiter)) != string::npos)
			{
			    token = val.substr(0, pos);
			    result[cI].push_back(token);
			    val.erase(0, pos + delimiter.length());
			    cI++;
			}
			result[cI].push_back(val);
		}
	}
	data = result;

	myFile.close();
}

void Parser::print()
{
	vector<vector<string>> vect = data;

	for (int i = 0; i < vect.size(); i++)
	    {
	        for (int j = 0; j < vect[i].size(); j++)
	        {
	            cout << vect[i][j] << " ; ";
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

Parser::~Parser() {}

