//
// Created by roy on 12/18/18.
//

#include "LineParser.h"

/**
 * Constructor of LineParser, used for parsing single line.
 * @param symbolTable symbol table for variables access.
 */
LineParser::LineParser(SymbolTable *symbolTable, DataReaderServer *dataReaderServer, DataSender * newDataSender) {
    this->symbolTable = symbolTable;
    this->dataReaderServer = dataReaderServer;
    this->util.set(this->symbolTable, this->dataReaderServer);
    this->dataSender = newDataSender;
}

int LineParser::parse(vector<string> stringVector, int startIndex) {
    string commandString = stringVector.at(startIndex); // first string will represent the first command in line.
    Commands command = commandMap.getCommand(commandString);
    if (stringVector.at(startIndex + 1) == "=") {
        command = Equal;
    }
    int indexJumpValue = 0;

    // for each command option - execute the fitting operation:
    switch (command) {
        case OpenDataServer : {
            string port = util.shuntingYard(smallLexer.lexer(stringVector.at(startIndex + 1)));
            string herz = util.shuntingYard(smallLexer.lexer(stringVector.at(startIndex + 2)));
            OpenServerCommand openServer(port, herz, this->dataReaderServer, this->symbolTable);
            indexJumpValue = openServer.execute();
            break;
        }

        case Connect : {
            ConnectCommand connect(stringVector.at(startIndex + 1), util.shuntingYard(smallLexer.lexer(stringVector.at(startIndex + 2))),
                                   this->dataSender);
            indexJumpValue = connect.execute();
            break;
        }

        case Var : {
            if (stringVector.size() == 5) {
                VarCommand varCommand(this->dataReaderServer, this->symbolTable, stringVector.at(startIndex + 1),
                                      stringVector.at(startIndex + 2), stringVector.at(startIndex + 3), stringVector.at(startIndex + 4));
                indexJumpValue = varCommand.execute();
            } else {
                VarCommand varCommand(this->dataReaderServer, this->symbolTable, stringVector.at(startIndex + 1),
                                      stringVector.at(startIndex + 2), stringVector.at(startIndex + 3));
                indexJumpValue = varCommand.execute();
            }
            break;
        }

        case Equal : {
            EqualCommand equalCommand(this->dataReaderServer, this->dataSender, stringVector.at(startIndex),
                                      stringVector.at(startIndex + 2), this->symbolTable);
            indexJumpValue = equalCommand.execute();
            break;
        }

        case Print : {
            string printString;
            // if the next string starts with quotes - string will be the string inside quotes.
            if (stringVector.at(startIndex + 1).at(0) == '"') {
                printString = stringVector.at(startIndex + 1).substr(1, stringVector.at(startIndex + 1).length() - 2);
            }
                // else, get the string value from symbol map.
                //if the next string starts as a number consider it a mathematical expression

            else if (stringVector.at(startIndex + 1).at(0) == '-' || stringVector.at(startIndex + 1).at(0) == '(' ||
                     isdigit(stringVector.at(startIndex + 1).at(0))) {
                printString = util.shuntingYard(smallLexer.lexer(stringVector.at(startIndex + 1)));
            }
            else {
                //check if its a local variable
                if (this->symbolTable->isInMap(stringVector.at(startIndex + 1))) {
                    printString = to_string(this->symbolTable->get(stringVector.at(startIndex + 1)));
                    //check if its a global variable
                } else if (this->symbolTable->isInMap(this->dataReaderServer->getBindAddress(stringVector.at(startIndex + 1)))) {
                    printString = to_string(
                            this->symbolTable->get(this->dataReaderServer->getBindAddress(stringVector.at(startIndex + 1))));
                } else {
                    cout << "Var not in symbol map" << "\n";
                }
            }

            PrintCommand printCommand(printString);
            indexJumpValue = printCommand.execute();
            break;
        }

        case Sleep : {
            // sleeps for the given amount of time.
            vector<string> stringExp = this->smallLexer.lexer(stringVector.at(startIndex + 1));
            SleepCommand sleepCommand(stod(this->util.shuntingYard(stringExp)));
            indexJumpValue = sleepCommand.execute();
            break;
        }

            // if the command is invalid command, throw.
        default:
            throw "No such Command";
    }

    return indexJumpValue;
}