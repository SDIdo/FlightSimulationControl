/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mult.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:10 PM
 */

#ifndef MULT_H
#define MULT_H
#include "BinaryExpression.h"

class Mult : public BinaryExpression {
public:
    Mult() = default;
    Mult(Expression*, Expression*);

    ~Mult() = default;
    virtual double calculate();
};

#endif /* MULT_H */

