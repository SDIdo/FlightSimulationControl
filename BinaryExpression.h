/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryExpression.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:43 PM
 */

#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H
#include "Expression.h"

class BinaryExpression : public Expression{
    public:
    Expression* left;
    Expression* right;
    virtual void set(Expression*, Expression*);
    virtual double calculate() = 0;
};


#endif /* BINARYEXPRESSION_H */

