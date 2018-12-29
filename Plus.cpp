//
// Created by roy on 12/24/18.
//

#include "Plus.h"
#include <iostream>

double Plus::calculate() {
    return (left->calculate() + right->calculate());
}
