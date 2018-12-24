/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mult.h" 
#include <iostream>
#include <string>
using namespace std;

Mult::Mult(Expression* newLeft, Expression* newRight) {
    left = newLeft;
    right = newRight;
}

double Mult::calculate() {
    cout << to_string(left->calculate()) << "\n";
    cout << to_string(right->calculate()) << "\n";
    return ((left->calculate()) * (right->calculate()));
}