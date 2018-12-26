//
// Created by roy on 12/18/18.
//

#include <iostream>
#include "LineParser.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "VarCommand.h"

/**
 * Constructor of LineParser, used for parsing single line.
 * @param symbolTable symbol table for variables access.
 */
LineParser::LineParser(SymbolTable *symbolTable) {
    this->symbolTable = symbolTable;
    this->util.set(this->symbolTable);
}

int LineParser::parse(vector<string> stringVector, int startIndex) {
    string commandString = stringVector.at(startIndex); // first string will represent the first command in line.
    Commands command = commandMap.getCommand(commandString);
    if (stringVector.at(1) == "=") {
        command = Equal;
    }
    int indexJumpValue = 0;

    // for each command option - execute the fitting operation:
    switch (command) {

        case OpenDataServer : {
            string port = util.shuntingYard(smallLexer.lexer(stringVector.at(1)));
            string herz = util.shuntingYard(smallLexer.lexer(stringVector.at(2)));
            OpenServerCommand openServer(port, herz, &this->dataReaderServer, this->symbolTable);
            cout << "So let's see what's about to be opened " << port << ", " << herz << "\n";
            indexJumpValue = openServer.execute();
            // create port and hertz, and open data server.
//            openServer.execute(stringVector.at(1), stringVector.at(2));
            break;
        }

        case Connect : { //Is Complete.
            ConnectCommand connect(stringVector.at(1), util.shuntingYard(smallLexer.lexer(stringVector.at(2))),
                                   &this->dataSender);
            indexJumpValue = connect.execute();
            break;
        }

        case Var : {
            // THIS 3 LINES IS WHAT NEEDS TO HAPPEN :
//            VarCommand varCommand(stringVector.at(1), stringVector.at(2),
//                                  stringVector.at(3), stringVector.at(4), this->dataReaderServer);
//            indexJumpValue = varCommand.execute();


            // from the likes of var x = 8
            cout << "Here with " << stringVector.at(3) << "\n";

            // if the command was bind:
            if ((stringVector.at(2) == "=") && (stringVector.at(3) == "bind")) {
                cout << "Time to update bind map!\n";
                this->dataReaderServer.setBind(stringVector.at(1), stringVector.at(4));
                indexJumpValue = 5;
            }
                // else, the variable is a local variable, and not binded var:
            else {
                string expressionAfterEquation = util.shuntingYard(smallLexer.lexer(stringVector.at(3)));
                symbolTable->set(stringVector.at(1), stod(expressionAfterEquation));
                cout << "Now let's see.. " << symbolTable->get(stringVector.at(1)) << "\n";
                indexJumpValue = 4;
            }
            break;
        }

        case Equal : {
            cout << "Here with " << stringVector.at(0) << "=" << stringVector.at(2) << "\n";
            //SCAT - have to initialize dataReader first?
            if (this->dataReaderServer.isInBindMap(stringVector.at(0))) {  //SCAT like it is not there.. seg?
                cout << "[Line parser] Yep it is binded. Updating server\n";
                string address = this->dataReaderServer.getBindAddress(stringVector.at(0));

                symbolTable->set(address,
                                 stod(this->util.shuntingYard(this->smallLexer.lexer(stringVector.at(2)))));

                address = address.substr(1, address.length() - 2); // cut the qoutes from the address.

                cout << "After te search\n";
                string update = " " + stringVector.at(2);
                string updatedAddress = address + update;

                char toSend[256];
                strcpy(toSend, updatedAddress.c_str());

                this->dataSender.sendCommand(toSend);
            } else {
                cout << "[Line Parser] No need to update in server that's a local var\n";
                symbolTable->set(stringVector.at(0), stod(this->
                        util.shuntingYard(this->smallLexer.lexer(stringVector.at(2)))));
            }
            indexJumpValue = 3;
            break;
        }

        case Print : {
            string printString;
            // if the next string starts with quotes - string will be the string inside quotes.
            if (stringVector.at(startIndex + 1).at(0) == '"') {
                printString = stringVector.at(startIndex + 1).substr(1,
                                                                     stringVector.at(startIndex + 1).length() - 2);
            }
                // else, get the string value from symbol map.
            else {
                if (this->symbolTable->isInMap(stringVector.at(1))) {
                    printString = to_string(this->symbolTable->get(stringVector.at(1)));
                } else if (this->symbolTable->isInMap(this->dataReaderServer.getBindAddress(stringVector.at(1)))) {
                    printString = to_string(
                            this->symbolTable->get(this->dataReaderServer.getBindAddress(stringVector.at(1))));
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

            // if the command is invalid command, throw error message.
        default:
            throw "Non valid command";
    }

    return
            indexJumpValue;

}