/*
 * File:   Div.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:13 PM
 */

#ifndef PROJECTPART1_DIV_H
#define PROJECTPART1_DIV_H

#include "BinaryExpression.h"

/**
 * Div is a binary expression used for division between two expressions.
 * Implements BinaryExpression.
 */
class Div : public BinaryExpression {
public:
    virtual double calculate();
};


#endif //PROJECTPART1_DIV_H
