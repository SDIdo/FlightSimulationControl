/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: idox
 *
 * Created on December 17, 2018, 8:36 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "Expression.h"
#include "Number.h"
#include "Plus.h"
#include "Minus.h"
#include "Mult.h"
#include "Div.h"
#include "Lexer.h"
#include "Utilities.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Welcome to Dugma!\n";
    Lexer lex;
    Utilities ut;
    cout << ut.shunting_yard(lex.run()) << "\n";
//    vector<string> h0 = lexer.run();
//    cout << ut.shunting_yard({"2", "+", "2"}) << endl;
//    Utilities.shunting_yard(lex.run());
    
//    cout << "This is the mult " << (new Mult(new Number("2"), new Number("2")))->calculate() << "\n";
    
    return 0;
}

