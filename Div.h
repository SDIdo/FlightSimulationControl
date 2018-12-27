/*
 * File:   Div.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:13 PM
 */

#ifndef PROJECTPART1_DIV_H
#define PROJECTPART1_DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {
public:
    Div() = default;
    Div(Expression*, Expression*);
    ~Div() = default;
    virtual double calculate();
};


#endif //PROJECTPART1_DIV_H
