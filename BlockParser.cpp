//
// Created by roy on 12/22/18.
//

#include <iostream>
#include <chrono>
#include "BlockParser.h"
#include "IfCommand.h"
#include "WhileCommand.h"

/**
 * Constructor of BlockParser, used for parsing blocks of strings.
 * @param symbolTable symbol table for variables access.
 * @param dataReaderServer data reader server for access to the bind map.
 * @param dataSender data sender for sending data through commands.
 */
BlockParser::BlockParser(SymbolTable *symbolTable, DataReaderServer *dataReaderServer, DataSender* newDataSender) {
    this->symbolTable = symbolTable;
    this->dataReaderServer = dataReaderServer;
    this->dataSender = newDataSender;
    this->util.set(this->symbolTable, this->dataReaderServer);
}

/**
 * This method parses the given strings vector and executes the matching commands
 * by their order. The block will be of two types: If block or While block.
 * @param stringVector vector of strings representing the commands and parameters.
 */
void BlockParser::parse(vector<string> stringVector) {
    string condition, exp1String, exp2String;
    vector<string> valueVector1, valueVector2;
    string commandString = stringVector.at(0); // first string will represent the command (if/while).
    Commands command = commandMap.getCommand(commandString);

    // prepares the expressions and condition for the IfCommand / WhileCommand:

    condition = stringVector.at(2); // condition of the if or while.
    exp1String = stringVector.at(1);
    exp2String = stringVector.at(3);

    // erase the beginning of the vector.
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());

    // for each command option - execute the fitting operation:
    switch (command) {

        case If : {
            IfCommand ifCommand(stringVector, exp1String, exp2String, condition,
                                this->symbolTable, this->dataReaderServer, this->dataSender);
            ifCommand.execute();
            break;
        }
        case While : {
            WhileCommand whileCommand(stringVector, exp1String, exp2String, condition,
                                      this->symbolTable, this->dataReaderServer, this->dataSender);
            whileCommand.execute();
            break;
        }
        // if the command was not valid.
        default:
            throw "Non valid command";
    }

}
