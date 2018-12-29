/*
 * File:   Mult.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:10 PM
 */

#ifndef PROJECTPART1_MULT_H
#define PROJECTPART1_MULT_H

#include "BinaryExpression.h"

/**
 * Minus is a binary expression used for multiplication between two expressions.
 * Implements BinaryExpression.
 */
class Mult : public BinaryExpression {
public:
    virtual double calculate();
};

#endif //PROJECTPART1_MULT_H
