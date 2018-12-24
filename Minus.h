/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Minus.h
 * Author: idox
 *
 * Created on December 17, 2018, 9:17 PM
 */

#ifndef MINUS_H
#define MINUS_H
#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus() = default;
    Minus(Expression*, Expression*);

    ~Minus() = default;
    virtual double calculate();
};

#endif /* MINUS_H */

