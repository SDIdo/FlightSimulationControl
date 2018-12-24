/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Number.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:37 PM
 */

#ifndef NUMBER_H
#define NUMBER_H
#include <string>
#include "Expression.h"
using namespace std;


class Number : public Expression{
    double value;
    public:
        Number(string);
        ~Number() = default;
    virtual double calculate();
};

#endif /* NUMBER_H */

