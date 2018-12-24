/*
 * File:   Minus.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:17 PM
 */

#ifndef PROJECTPART1_MINUS_H
#define PROJECTPART1_MINUS_H

#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus() = default;
    Minus(Expression*, Expression*);

    ~Minus() = default;
    virtual double calculate();
};


#endif //PROJECTPART1_MINUS_H
