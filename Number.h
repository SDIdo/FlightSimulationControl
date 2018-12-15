/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Number.h
 * Author: idox
 *
 * Created on December 13, 2018, 12:55 PM
 */

#ifndef NUMBER_H
#define NUMBER_H

#include "Expression.h"


class Number : public Expression 
{
    double value;
public:
    Number(double);
    ~Number();
    virtual double calculate();

};

#endif /* NUMBER_H */

