//
// Created by roy on 12/15/18.
//

#ifndef PROJECTPART1_EXPRESSIONCOMMAND_H
#define PROJECTPART1_EXPRESSIONCOMMAND_H

#include "Command.h"
#include "Expression.h"

/**
 * This class will be the connection between Expression and Command, as
 * it contains a Command and implements Expression.
 */
class ExpressionCommand : public Expression{
    Command* commandPtr;
public:
    ExpressionCommand(Command* commandPtr) {
        this->commandPtr = commandPtr;
    }
    virtual double calculate() {
        return commandPtr->execute();
    }
};

#endif //PROJECTPART1_EXPRESSIONCOMMAND_H
