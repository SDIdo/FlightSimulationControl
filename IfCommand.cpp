//
// Created by roy on 12/22/18.
//

#include "IfCommand.h"
#include "LineParser.h"

IfCommand::IfCommand(vector<string> commandStringVector, double exp1Val, double exp2Val,
        string condition, SymbolTable *symbolTablePtr){
    this->commandStringVector = commandStringVector;
    this->exp1Val = exp1Val;
    this->exp2Val = exp2Val;
    this->condition = condition;
    this->symbolTablePtr = symbolTablePtr;
}

int IfCommand::execute() {
    // if the condition is not met, return from the function.
    if (!this->conditionIsMet()) {
        return 0;
    }
    // else, condition is met and method executes each command:
    int i = 0;
    int commandLength;
    LineParser lineParser(this->symbolTablePtr);
    while (i < commandStringVector.size()) {
        Command command = 1st in array;
        commandLength = command.execute();
        i += command.execute();
    }
    return i + 1;
}
