/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lexer.h
 * Author: idox
 *
 * Created on December 18, 2018, 4:18 AM
 */

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

using namespace std;

class Lexer {
public:
    vector<string> run();
    vector<string> lexer(string);
    bool isOperator(char c);
};

#endif /* LEXER_H */

