//
// Created by roy on 12/22/18.
//

#include "IfCommand.h"
#include "LineParser.h"

/**
 * Constructor of if command.
 * @param commandStringVector vector of the strings representing the commands in the if block.
 * @param exp1String first expression, represented as a string.
 * @param exp2String second expression, represented as a string.
 * @param condition condition for the execution of the block, represented as a string.
 * @param symbolTablePtr symbol table of the values.
 * @param dataReaderServer data reader server for the check in bind map.
 * @param dataSender data sender for the execution of assigning commands.
 */
IfCommand::IfCommand(vector<string> commandStringVector, string exp1String, string exp2String,
        string condition, SymbolTable *symbolTablePtr, DataReaderServer *dataReaderServer, DataSender * newDataSender){
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
 * This method checks if the condition is met. If it does - it executes
 * each line given by the client.
 * @return jump for the lexer.
 */
int IfCommand::execute() {
    // if the condition is not met, return from the function.
    if (!this->conditionIsMet()) {
        return 0;
    }
    // else, condition is met and method executes each command:
    int i = 0;
    int commandLength;
    LineParser lineParser(this->symbolTablePtr, this->dataReaderServer, this->dataSender);
    // parser executes each line command. does not work with nested loops...
    while (i < this->commandStringVector.size()) {
        commandLength = lineParser.parse(this->commandStringVector, i);
        i += commandLength;
    }
    return i + 1;
}
