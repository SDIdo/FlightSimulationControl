//
// Created by roy on 12/24/18.
//

#include "Div.h"

Div::Div(Expression *newLeft, Expression *newRight) {
    left = newLeft;
    right = newRight;
}

double Div::calculate() {
    return (left->calculate() / right->calculate());
}