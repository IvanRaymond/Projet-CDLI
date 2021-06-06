/*
 * parser.cpp
 *
 *  Created on: 22 Apr 2021
 *      Author: ivan
 * Description: A simple CSV parser that stores the csv into a 2D Vector.
 */

#include "parser.h"
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;

parser::~parser() {}

parser::parser(){}

parser::parser(string fileName)
{
    parse(fileName);
}

/*
 * Parsing method
 * Stores the result in the parameter data of the parser class
 */
void parser::parse(string fileName)
{
    file = fileName;

    string l, c, val;
    int cI;
    ifstream myFile(fileName);
    vector<vector<string>> result;

    // Replace with call to Qt to show Message Box
    // Or catch error and display
    if(!myFile.is_open()) throw runtime_error("Fichier introuvable");

    // ToDo add comments
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

/*
 * Returns the number of columns in the dataset
 */
int parser::getColumnCount(){
    return data.size();
}

/*
 * Return the number of rows in the dataset
 */
int parser::getRowCount(){
    vector<string> col;
    col = data[0];
    return col.size();
}

void parser::setFile(string fileName)
{
    file = fileName;
}

void parser::setEncoding(string encoding)
{
    delimiter = encoding;
}

vector<vector<string>> parser::getData()
{
    return data;
}



