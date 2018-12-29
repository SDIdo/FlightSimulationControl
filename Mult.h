/*
 * File:   Mult.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:10 PM
 */

#ifndef PROJECTPART1_MULT_H
#define PROJECTPART1_MULT_H

#include "BinaryExpression.h"

class Mult : public BinaryExpression {
public:
    Mult() = default;
    Mult(Expression*, Expression*);

    ~Mult() = default;
    virtual double calculate();
};

#endif //PROJECTPART1_MULT_H
