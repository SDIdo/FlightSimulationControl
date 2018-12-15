/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "BinaryExpression.h"
#include "Number.h"
#include <string>

using namespace std;


BinaryExpression::BinaryExpression(Expression* newLeft, string operation ,Expression* newRight){
    left = newLeft;
    right = newRight;
    oper = operation;
}
BinaryExpression::BinaryExpression(double newLeft, double newRight){
    left = new Number(newLeft);
    right = new Number(newRight);
}
BinaryExpression::BinaryExpression(double newLeft, Expression* newRight){
    left = new Number(newLeft);
    right = newRight;
}
BinaryExpression::BinaryExpression(Expression* newLeft, double newRight){
    left = newLeft;
    right = new Number(newRight);
}
double BinaryExpression::calculate(){
    switch(oper){
    case "+":
        return left->calculate() + right->calculate(); //@TODO staticating + for now!
    default:
        return 0;
}