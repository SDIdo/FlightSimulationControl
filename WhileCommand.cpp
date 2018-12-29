//
// Created by roy on 12/24/18.
//

#include "WhileCommand.h"
#include "LineParser.h"

/**
 * Constructor of while command.
 * @param commandStringVector vector of the strings representing the commands in the if block.
 * @param exp1String first expression, represented as a string.
 * @param exp2String second expression, represented as a string.
 * @param condition condition for the execution of the block, represented as a string.
 * @param symbolTablePtr symbol table of the values.
 * @param dataReaderServer data reader server for the check in bind map.
 * @param dataSender data sender for the execution of assigning commands.
 */
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

/**
 * This method checks if the condition is met, and as long as
 * it does - it executes each line given by the client.
 * @return jump for the lexer.
 */
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
