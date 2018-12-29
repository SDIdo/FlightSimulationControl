//
// Created by roy on 12/24/18.
//

#include "Minus.h"

/**
 * This method calculates the subtraction between left and right expressions.
 * @return double value of the operation.
 */
double Minus::calculate() {
    return (left->calculate() - right->calculate());
}