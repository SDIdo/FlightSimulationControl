/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Plus.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:48 PM
 */

#ifndef PLUS_H
#define PLUS_H
#include <string>
#include "BinaryExpression.h"

using namespace std;
class Plus : public BinaryExpression{
    public:
        Plus() = default;
        Plus(Expression*, Expression*);
        ~Plus() = default;
        virtual double calculate();
};

#endif /* PLUS_H */

