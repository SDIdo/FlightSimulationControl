//
// Created by roy on 12/24/18.
//

#include "Number.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Constructor of a number. receives the value string and saves the value as double.
 * @param newValue
 */
Number::Number(string newValue) {
    value = stod(newValue);
}

/**
 * This method returns the value of the number.
 * @return double value of the number.
 */
double Number::calculate() {
    return value;
}