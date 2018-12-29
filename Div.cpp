//
// Created by roy on 12/24/18.
//

#include "Div.h"

double Div::calculate() {
    return (left->calculate() / right->calculate());
}