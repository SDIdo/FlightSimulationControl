/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryExpression.h
 * Author: idox
 *
 * Created on December 13, 2018, 12:52 PM
 */

#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H
#include "Expression.h"
#include <string>
using namespace std;

class BinaryExpression : public Expression{
    Expression* left;
    Expression* right;
    string oper;
public:
    BinaryExpression(Expression*, string, Expression*);
    BinaryExpression(double, double);
    BinaryExpression(double, Expression*);
    BinaryExpression(Expression*, double);
    virtual double calculate();

};

#endif /* BINARYEXPRESSION_H */

