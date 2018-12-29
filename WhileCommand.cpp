//
// Created by roy on 12/24/18.
//

#include "WhileCommand.h"
#include "LineParser.h"

WhileCommand::WhileCommand(vector<string> commandStringVector, string exp1String, string exp2String,
                           string condition, SymbolTable *symbolTablePtr, DataReaderServer *dataReaderServer, DataSender * newDataSender) {
    this->commandStringVector = commandStringVector;
    this->exp1String = exp1String;
    this->exp2String = exp2String;
    this->condition = condition;
    this->symbolTablePtr = symbolTablePtr;
    this->dataReaderServer = dataReaderServer;
    this->dataSender = newDataSender;
    this->util.set(this->symbolTablePtr,this->dataReaderServer);
}

int WhileCommand::execute() {
    int i = 0;
    // if the condition is not met, return from the function.
    if (!this->conditionIsMet()) {
        return 0;
    }
    // else, while condition is met, the method executes each command:
    while (this->conditionIsMet()) {
        int i = 0;
        int commandLength;
        LineParser lineParser(this->symbolTablePtr, this->dataReaderServer, this->dataSender);
        // parser executes each line command. does not work with nested loops...
        while (i < this->commandStringVector.size()) {
            commandLength = lineParser.parse(this->commandStringVector, i);
            i += commandLength;
        }
    }
    return i + 1;
}
