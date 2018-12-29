//
// Created by roy on 12/24/18.
//

#include "Minus.h"

Minus::Minus(Expression* newLeft, Expression* newRight) {
    left = newLeft;
    right = newRight;
}

double Minus::calculate() {
    return (left->calculate() - right->calculate());
}