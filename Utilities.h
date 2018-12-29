/*
 * File:   Utilities.h
 * Author: idox
 *
 * Created on December 20, 2018, 5:05 PM
 */

#ifndef PROJECTPART1_UTILITIES_H
#define PROJECTPART1_UTILITIES_H

#include "SymbolTable.h"
#include "DataReaderServer.h"
#include <unordered_map>
#include "BinaryExpression.h"
#include <string>
#include <vector>
using namespace std;

class Utilities {
    unordered_map<string, BinaryExpression*> operators;
    SymbolTable* symbols;
    DataReaderServer* dataServer;
public:
    Utilities();
    ~Utilities() = default;
    void set(SymbolTable*, DataReaderServer*);
    string shuntingYard(vector<string> instream);
    int precedence(string);
};

#endif //PROJECTPART1_UTILITIES_H
