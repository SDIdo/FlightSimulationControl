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
    cout << "[$ LineParser $] sockfd is : " <<  this->dataSender->getSock() << "\n";
    string commandString = stringVector.at(startIndex); // first string will represent the first command in line.
    cout << "#@#line Parser with command: " << stringVector.at(startIndex) << " at start index :" << startIndex <<"\n";
    Commands command = commandMap.getCommand(commandString);
    if (stringVector.at(1) == "=") {
        command = Equal;
    }
    int indexJumpValue = 0;

    // for each command option - execute the fitting operation:
    switch (command) {
        case OpenDataServer : {
            cout << "[$ LineParser_openData $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            string port = util.shuntingYard(smallLexer.lexer(stringVector.at(1)));
            string herz = util.shuntingYard(smallLexer.lexer(stringVector.at(2)));
            OpenServerCommand openServer(port, herz, this->dataReaderServer, this->symbolTable);
            cout << "So let's see what's about to be opened " << port << ", " << herz << "\n";
            indexJumpValue = openServer.execute();
            break;
        }

        case Connect : {
            cout << "[$ LineParser_Connect $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            ConnectCommand connect(stringVector.at(1), util.shuntingYard(smallLexer.lexer(stringVector.at(2))),
                                   this->dataSender);
            indexJumpValue = connect.execute();
            break;
        }

        case Var : {
            cout << "[$ LineParser_Var $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            if (stringVector.size() == 5) {
                VarCommand varCommand(this->dataReaderServer, this->symbolTable, stringVector.at(1),
                                      stringVector.at(2), stringVector.at(3), stringVector.at(4));
                indexJumpValue = varCommand.execute();
            } else {
                VarCommand varCommand(this->dataReaderServer, this->symbolTable, stringVector.at(1),
                                      stringVector.at(2), stringVector.at(3));
                indexJumpValue = varCommand.execute();
            }
            break;
        }

        case Equal : {
            cout << "[Equal from outside] Here in equal command with " << stringVector.at(0) << stringVector.at(1) << stringVector.at(2) << "\n";
            cout << "[Equal from outside] And client sockfd is " << this->dataSender->getSock() << "\n";
            EqualCommand equalCommand(this->dataReaderServer, this->dataSender, stringVector.at(0),
                                      stringVector.at(2), this->symbolTable);
            indexJumpValue = equalCommand.execute();
            break;
        }

        case Print : {
            cout << "[$ LineParser_Print $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            string printString;
            // if the next string starts with quotes - string will be the string inside quotes.
            if (stringVector.at(1).at(0) == '"') {
                printString = stringVector.at(1).substr(1, stringVector.at(1).length() - 2);
            }
                // else, get the string value from symbol map.
                //if the next string starts as a number consider it a mathematical expression

            else if (stringVector.at(1).at(0) == '-' || stringVector.at(1).at(0) == '(' ||
                     isdigit(stringVector.at(1).at(0))) {
                cout << "Detected a math operation to print\n";
                printString = util.shuntingYard(smallLexer.lexer(stringVector.at(1)));
            }
            else {
                //check if its a local variable
                if (this->symbolTable->isInMap(stringVector.at(1))) {
                    printString = to_string(this->symbolTable->get(stringVector.at(1)));
                    //check if its a global variable
                } else if (this->symbolTable->isInMap(this->dataReaderServer->getBindAddress(stringVector.at(1)))) {
                    printString = to_string(
                            this->symbolTable->get(this->dataReaderServer->getBindAddress(stringVector.at(1))));
                } else {
                    cout << "Var not in symbol map" << "\n";
                }
            }

            PrintCommand printCommand(printString);
            indexJumpValue = printCommand.execute();
            break;
        }

        case Sleep : {
            cout << "[$ LineParser_Sleep $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            // sleeps for the given amount of time.
            vector<string> stringExp = this->smallLexer.lexer(stringVector.at(startIndex + 1));
            SleepCommand sleepCommand(stod(this->util.shuntingYard(stringExp)));
            indexJumpValue = sleepCommand.execute();
            break;
        }

            // if the command is invalid command, print error message.
        default:
            cout << "[$ LineParser_No Such $] sockfd is : " <<  this->dataSender->getSock() << "\n";
            cout << "command is" << stringVector.at(1) << endl;
            sleep(100);
            cout << "No such Command\n";
    }

    return indexJumpValue;
}