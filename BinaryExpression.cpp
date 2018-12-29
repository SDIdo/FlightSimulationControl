//
// Created by roy on 12/24/18.
//

#include "BinaryExpression.h"

/**
 * This method sets left and right expressions to the expression.
 * @param newLeft left expression.
 * @param newRight right expression.
 */
void BinaryExpression::set(Expression *newLeft, Expression *newRight) {
    left = newLeft;
    right = newRight;
}