/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: idox
 *
 * Created on December 13, 2018, 12:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Number.h"
#include "BinaryExpression.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Hola\n";
    
    
    //I should get from the parser numbers which I'll make expressions
    //and I'll get an operator as well 
    double a = 1;
    double b = 2;
    double c = 6;
    string p = "+";
    Expression* e = new BinaryExpression(new Number(a), p, new Number(b));
    
    cout << e->calculate() << endl;
    
    
    return 0;
}

