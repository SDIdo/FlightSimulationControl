/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Div.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:13 PM
 */

#ifndef DIV_H
#define DIV_H
#include "BinaryExpression.h"
class Div : public BinaryExpression {
public:
    Div() = default;
    Div(Expression*, Expression*);
    ~Div() = default;
    virtual double calculate();
};

#endif /* DIV_H */

