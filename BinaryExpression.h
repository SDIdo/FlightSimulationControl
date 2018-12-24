/*
 * File:   BinaryExpression.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:43 PM
 */

#ifndef PROJECTPART1_BINARYEXPRESSION_H
#define PROJECTPART1_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression{
public:
    Expression* left;
    Expression* right;
    virtual void set(Expression*, Expression*);
    virtual double calculate() = 0;
};


#endif //PROJECTPART1_BINARYEXPRESSION_H
