//
// Created by roy on 12/24/18.
//

#include "Mult.h"
#include <iostream>
#include <string>
using namespace std;

double Mult::calculate() {
    return ((left->calculate()) * (right->calculate()));
}
