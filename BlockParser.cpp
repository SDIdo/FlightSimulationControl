//
// Created by roy on 12/22/18.
//

#include <iostream>
#include <chrono>
#include "BlockParser.h"
#include "IfCommand.h"

/**
 * Constructor of BlockParser, used for parsing blocks of strings.
 * @param symbolTable symbol table for variables access.
 */
BlockParser::BlockParser(SymbolTable *symbolTable) {
    this->symbolTable = symbolTable;
}

void BlockParser::parse(vector<string> stringVector) {
    string commandString = stringVector.at(0); // first string will represent the command (if/while).
    Commands command = commandMap.getCommand(commandString);

    // prepares the expressions and condition for the IfCommand / WhileCommand.
    double exp1 = shuntingYard(stringVector.at(1));
    string condition = stringVector.at(2);
    double exp2 = shuntingYard(stringVector.at(3));

    // for each command option - execute the fitting operation:
    switch (command) {

        case If :

            IfCommand ifCommand(stringVector, exp1, exp2, condition, this->symbolTable);
            ifCommand.execute();
            break;

//        case While :
//            //     while()
//            WhileCommand whileCommand(stringVector, exp1, exp2, condition);
//            whileCommand.execute();
//            break;

        default:
            throw "Non valid command";
    }

}
