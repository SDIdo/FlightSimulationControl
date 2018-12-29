/*
 * File:   Plus.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:48 PM
 */

#ifndef PROJECTPART1_PLUS_H
#define PROJECTPART1_PLUS_H

#include <string>
#include "BinaryExpression.h"

using namespace std;

class Plus : public BinaryExpression{
public:
    virtual double calculate();
};


#endif //PROJECTPART1_PLUS_H
