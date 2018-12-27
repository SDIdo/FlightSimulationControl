/*
 * File:   Utilities.h
 * Author: idox
 *
 * Created on December 20, 2018, 5:05 PM
 */

#ifndef PROJECTPART1_UTILITIES_H
#define PROJECTPART1_UTILITIES_H

#include "SymbolTable.h"
#include <map>
#include "BinaryExpression.h"
#include <string>
#include <vector>
using namespace std;

class Utilities {
    map<string, BinaryExpression*> operators;
    SymbolTable symbolsTable;
public:
    Utilities();
    ~Utilities();
    void set(SymbolTable&);
    string shuntingYard(vector<string> instream, SymbolTable&);
    int precedence(string);
};

#endif //PROJECTPART1_UTILITIES_H
