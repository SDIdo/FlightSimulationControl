//
// Created by roy on 12/24/18.
//

#include "Mult.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * This method calculates the multiplication between left and right expressions.
 * @return double value of the operation.
 */
double Mult::calculate() {
    return ((left->calculate()) * (right->calculate()));
}
