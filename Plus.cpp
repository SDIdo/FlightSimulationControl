//
// Created by roy on 12/24/18.
//

#include "Plus.h"
#include <iostream>

Plus::Plus(Expression *newLeft, Expression *newRight) {
    left = newLeft;
    right = newRight;
}

double Plus::calculate() {
    return (left->calculate() + right->calculate());
}
