# Projet de Culture des Langages Informatique

## Table of contents
* [General info](#general-info)
* [Features](#features)
* [Classes](#classes)
* [Technologies](#technologies)
* [Setup](#setup)

##General info
This project is a CSV manipulation program.

##Features
* Opening CSV
* Modifying the CSV
* Saving the CSV
* Calculations on CSV
* Data preprocessing of CSV

##Classes

####Parser
The parser class contains the methods to parse the CSV file into a vector of vectors. Each vectors contains a column.

####DataPreprocessor
Inspired by Python SimpleImputer. Replaces numerical missing values by a replacement strategy. The replacement strategy is in the ImputerStrategy class.

####ImputerStrategy
Interface giving the blueprint to implement replacement strategies into the DataPreprocessor.

####Operation
Class containing csv calculations on rows and columns.

###CSV Operations Available(on Rows or Columns)
* Sum
* Average
* Median
* Max

##Technologies
Project is created with:
* Qt version: 6.0.3
* C++

##Setup :

To run this project, compile it using qmake:

```
*In src folder*
$ qmake
$ make
$ ./spreadsheet
```



