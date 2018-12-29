/*
 * File:   Minus.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:17 PM
 */

#ifndef PROJECTPART1_MINUS_H
#define PROJECTPART1_MINUS_H

#include "BinaryExpression.h"

/**
 * Minus is a binary expression used for subtraction between two expressions.
 * Implements BinaryExpression.
 */
class Minus : public BinaryExpression {
public:
    virtual double calculate();
};


#endif //PROJECTPART1_MINUS_H
