/*
 * parser.cpp
 *
 *  Created on: 22 Apr 2021
 *      Author: ivan
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

void parser::save(QVector<QVector<QString>> X)
{
    QFile file("out.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);

    QVector<QVector<QString>> vect = X;
    int colSize = vect[0].size();
    for (int i = 0; i < colSize; i++)
    {
        for (int j = 0; j < vect.size(); j++)
        {
            colSize = vect[j].size();
            out << vect[j][i];
            if (j < vect.size() - 1) {
                out << ";";
            }
        }
        out << "\n";
    }
}

void parser::print()
{
    vector<vector<string>> vect = data;
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

int parser::getColumnCount(){
    return data.size();
}

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



