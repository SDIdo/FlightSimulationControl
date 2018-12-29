//
// Created by roy on 12/24/18.
//

#include "Minus.h"

double Minus::calculate() {
    return (left->calculate() - right->calculate());
}