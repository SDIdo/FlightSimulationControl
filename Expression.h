//
// Created by roy on 12/15/18.
//

#ifndef PROJECTPART1_EXPRESSION_H
#define PROJECTPART1_EXPRESSION_H

/**
 * Interface of expressions, which could be calculated.
 */
class Expression{
public:
    virtual double calculate() = 0;
    virtual ~Expression() = default;
};

#endif //PROJECTPART1_EXPRESSION_H
