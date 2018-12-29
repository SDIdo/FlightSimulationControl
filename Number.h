/*
 * File:   Number.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:37 PM
 */

#ifndef PROJECTPART1_NUMBER_H
#define PROJECTPART1_NUMBER_H

#include <string>
#include "Expression.h"

using namespace std;

/**
 * Number holds a double value.
 * Implements Expression, therefore could be calculated and return the value.
 */
class Number : public Expression {
    double value;
public:
    Number(string);
    ~Number() = default;
    virtual double calculate();
};


#endif //PROJECTPART1_NUMBER_H
