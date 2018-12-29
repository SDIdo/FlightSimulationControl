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
 */
BlockParser::BlockParser(SymbolTable *symbolTable, DataReaderServer *dataReaderServer, DataSender* newDataSender) {
    this->symbolTable = symbolTable;
    this->dataReaderServer = dataReaderServer;
    this->dataSender = newDataSender;
    this->util.set(this->symbolTable, this->dataReaderServer);
}

void BlockParser::parse(vector<string> stringVector) {
    string condition, exp1String, exp2String;
    vector<string> valueVector1, valueVector2;
    string commandString = stringVector.at(0); // first string will represent the command (if/while).
    Commands command = commandMap.getCommand(commandString);

    // prepares the expressions and condition for the IfCommand / WhileCommand:

    condition = stringVector.at(2); // condition of the if or while.
    exp1String = stringVector.at(1);
    exp2String = stringVector.at(3);

    // NEED TO DELETE BEGININNG OF VECTOR ("if", conditionals... )
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

        default:
            throw "Non valid command";
    }

}
