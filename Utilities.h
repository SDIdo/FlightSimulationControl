/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utilities.h
 * Author: idox
 *
 * Created on December 20, 2018, 5:05 PM
 */

#ifndef UTILITIES_H
#define UTILITIES_H
#include "SymbolTable.h"
#include <map>
#include "BinaryExpression.h"
#include <string>
#include <vector>
using namespace std;

class Utilities {
    map<string, BinaryExpression*> operators;
    SymbolTable* symbols;
public:
    Utilities();
    ~Utilities() = default;
    void set(SymbolTable*);
    string shuntingYard(vector<string> instream);
    int precedence(string);
};

#endif /* UTILITIES_H */

