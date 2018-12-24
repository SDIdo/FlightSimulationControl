/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "BinaryExpression.h"

void BinaryExpression::set(Expression* newLeft, Expression* newRight){
    left = newLeft;
    right = newRight;
}