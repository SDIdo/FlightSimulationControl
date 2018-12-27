//
// Created by roy on 12/22/18.
//

#include "IfCommand.h"
#include "LineParser.h"

IfCommand::IfCommand(vector<string> commandStringVector, string exp1String, string exp2String,
        string condition, SymbolTable &symbolTablePtr){
    this->commandStringVector = commandStringVector;
    this->exp1String = exp1String;
    this->exp2String = exp2String;
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
    // parser executes each line command. does not work with nested loops...
    while (i < this->commandStringVector.size()) {
        commandLength = lineParser.parse(this->commandStringVector, i);
        i += commandLength;
    }
    return i + 1;
}
