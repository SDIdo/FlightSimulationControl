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
            openServer.execute();
            // create port and hertz, and open data server.
//            openServer.execute(stringVector.at(1), stringVector.at(2));
            break;
        }

        case Connect : { //Is Complete.
            ConnectCommand connect(stringVector.at(1), util.shuntingYard(smallLexer.lexer(stringVector.at(2))),
                                   &this->dataSender);
            connect.execute();
            break;
        }

        case Var : {
            // from the likes of var x = 8
            cout << "Here with " << stringVector.at(3) << "\n";

            if ((stringVector.at(2) == "=") && (stringVector.at(3) == "bind")) {
//                string expressionAfterEquation = ut.shuntingYard(smallLexer.lexer(stringVector.at(4)));
                cout << "Time to update bind map!\n";
                this->dataReaderServer.setBind(stringVector.at(1), stringVector.at(4));
            } else {
                string expressionAfterEquation = util.shuntingYard(smallLexer.lexer(stringVector.at(3)));
                char charAfterEquation = expressionAfterEquation.at(0);
                if (stringVector.at(2) == "=" && isdigit(charAfterEquation)) {
                    cout << "Detected var x = " << expressionAfterEquation << "\n";

                    cout << "Now check whether it's binded with the simulator..\n";

                    if (this->dataReaderServer.isInBindMap(stringVector.at(1))) {
                        cout << "Hmm so this x is binded!\n";
                        string address = stringVector.at(this->dataReaderServer.getFromBindValues(stringVector.at(1)));
                        string update = " " + stringVector.at(3);
                        string updatedAddress = address + update;

                        char toSend[256];
                        strcpy(toSend, updatedAddress.c_str());

                        this->dataSender.sendCommand(toSend);
                    } else {
                        symbolTable->set(stringVector.at(1), stod(expressionAfterEquation));
                        cout << "Now let's see.. " << symbolTable->get("x") << "\n";
                    }
                }
            }
//            symbolTable->set()
// put value in symbol table (Or if BIND, then bind with the relative folder).
            break;
        }

        case Equal : {
            cout << "Here with " << stringVector.at(0) << "=" << stringVector.at(2) << "\n";
            //SCAT - have to initialize dataReader first?
//            if (this-){
            if (this->dataReaderServer.isInBindMap(stringVector.at(0))) {  //SCAT like it is not there.. seg?
                cout << "[Line parser] Yep it is there. Updating server\n";
//                    this->dataReaderServer.setBind(stringVector.at(0), stringVector.at(2)); //SCAT like no expressions yet
                string address = stringVector.at(this->dataReaderServer.getFromBindValues(stringVector.at(0)));
                cout << "Aftr te serec\n";
                string update = " " + stringVector.at(2);
                string updatedAddress = address + update;

                char toSend[256];
                strcpy(toSend, updatedAddress.c_str());

                this->dataSender.sendCommand(toSend);
            }
//            }
            else {
                cout << "[Line Parser] No need to update in server that's a local var\n";
                symbolTable->set(stringVector.at(0), stod(stringVector.at(2)));
            }
            cout << "Just want to see.. " << symbolTable->get("x");
// input the next value to the previous value.
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
                printString = to_string(this->symbolTable->get(stringVector.at(1)));
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
    return indexJumpValue;

}