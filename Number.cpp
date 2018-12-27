//
// Created by roy on 12/24/18.
//

#include "Number.h"
#include <string>
#include <iostream>

using namespace std;

Number::Number(string newValue) {
    value = stod(newValue);
    cout << "[Number] value is now: " << value << "\n";
}

double Number::calculate() {
//    cout << "$$Got into calculate self\n";
    return value;
}