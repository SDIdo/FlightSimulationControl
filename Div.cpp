//
// Created by roy on 12/24/18.
//

#include "Div.h"

/**
 * This method calculates the division between left and right expressions.
 * @return double value of the operation.
 */
double Div::calculate() {
    return (left->calculate() / right->calculate());
}