//
// Created by roy on 12/24/18.
//

#include "Number.h"
#include <string>
#include <iostream>

using namespace std;

Number::Number(string newValue) {
    value = stod(newValue);
}

double Number::calculate() {
    return value;
}