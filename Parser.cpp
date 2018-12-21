//
// Created by roy on 12/18/18.
//

#include "Parser.h"

void Parser::parse(vector<string> stringVector) {
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

        case If :
            // if the condition on the line is met, executes the next line.
            break;

        case While :
            //read more lines and execute until gets to next curly brackets.
            break;

        case Print :
            // prints the next string (or symbol from symbol table) to the screen.
            break;

        case Sleep :
            // sleeps for the given amount of time.
            break;

            // if the command is invalid command, throw error message.
        default:
            throw "Non valid command";
    }

}