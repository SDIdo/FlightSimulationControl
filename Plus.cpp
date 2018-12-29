//
// Created by roy on 12/24/18.
//

#include "Plus.h"
#include <iostream>

/**
 * This method calculates the addition of left and right expressions.
 * @return double value of the operation.
 */
double Plus::calculate() {
    return (left->calculate() + right->calculate());
}
