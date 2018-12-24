//
// Created by roy on 12/18/18.
//

#include <iostream>
#include "LineParser.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"

/**
 * Constructor of LineParser, used for parsing single line.
 * @param symbolTable symbol table for variables access.
 */
LineParser::LineParser(SymbolTable *symbolTable) {
    this->symbolTable = symbolTable;
}

int LineParser::parse(vector<string> stringVector, int startIndex) {
    string commandString = stringVector.at(startIndex); // first string will represent the first command in line.
    Commands command = commandMap.getCommand(commandString);
    int indexJumpValue = 0;

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

        case Print : {
            string printString;
            // if the next string starts with quotes - string will be the string inside quotes.
            if (stringVector.at(startIndex + 1).at(0) == '"') {
                printString = stringVector.at(startIndex + 1).substr(1, stringVector.at(startIndex + 1).length() - 2);
            }
                // else, get the string value from symbol map.
            else {
                printString = to_string(this->symbolTable->get(stringVector.at(1)));
            }
            PrintCommand printCommand(printString);
            indexJumpValue = printCommand.execute();
            break;
        }

        case Sleep : {
            // sleeps for the given amount of time.
//            SleepCommand sleepCommand(shuntingYard(stringVector.at(startIndex + 1)));
//            indexJumpValue = sleepCommand.execute();
            break;
        }

            // if the command is invalid command, throw error message.
        default:
            throw "Non valid command";
    }
    return indexJumpValue;

}