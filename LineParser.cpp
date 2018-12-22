//
// Created by roy on 12/18/18.
//

#include <iostream>
#include <chrono>
#include "LineParser.h"
#include "IfCommand.h"

/**
 * Constructor of LineParser, used for parsing single line.
 * @param symbolTable symbol table for variables access.
 */
LineParser::LineParser(SymbolTable *symbolTable) {
    this->symbolTable = symbolTable;
}

void LineParser::parse(vector<string> stringVector) {
    string commandString = stringVector.at(0); // first string will represent the first command in line.
    Commands command = commandMap.getCommand(commandString);

    // for each command option - execute the fitting operation:
    switch (command) {
        case OpenDataServer :
            // create port and hertz, and open data server.
            break;

        case Connect :
            // connect as client to the flight gear.
            break;

        case Var :
            // put value in symbol table (and if BIND, then bind with the relative folder).
            break;

        case Bind : // MAYBE ITS NOT EVEN A COMMAND.
            // bind the variable to the next string.
            break;

        case Equal :
            // input the next value to the previous value.
            break;

        case Print :
            // if the next string starts with quotes - print it.
            if (stringVector.at(1).at(0) == '"') {
                cout << stringVector.at(1) << "\n";
            }
                // else, get the string value from symbol map and print it.
            else {
                cout << to_string(this->symbolTable->get(stringVector.at(1))) << "\n";
            }
            break;

        case Sleep :
            // sleeps for the given amount of time.
//            double sleepTime = shuntingYard(stringVector.at(1));
//            chrono::seconds(sleepTime);
            break;

            // if the command is invalid command, throw error message.
        default:
            throw "Non valid command";
    }

}