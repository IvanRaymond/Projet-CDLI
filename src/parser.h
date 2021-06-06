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

#include <QtWidgets>
#include <QDebug>
using namespace std;

//#define matrix vector<vector<string>>
//#define dataColumn vector<string>

class parser {

public:
    // Vecteur contenant les colonnes comme pair d'entete et vecteur contenant les valeurs
    vector<vector<string>> data;
    string delimiter = ";";
    string file;

    parser();
    parser(string fileName);

    void parse(string fileName);
    void setFile(string fileName);
    void setEncoding(string encoding);
    vector<vector<string>> getData();
    int getColumnCount();
    int getRowCount();

    virtual ~parser();
};

#endif /* PARSER_H_ */

