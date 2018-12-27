//
// Created by roy on 12/24/18.
//

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
