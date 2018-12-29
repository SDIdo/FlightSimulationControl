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
    cout << "entered block parser with sockfd" << this->dataSender->getSock() << endl;
    string condition, exp1String, exp2String;
    cout << "a\n";
    vector<string> valueVector1, valueVector2;
    cout << "b\n";
    string commandString = stringVector.at(0); // first string will represent the command (if/while).
    cout << "c\n";
    Commands command = commandMap.getCommand(commandString);
    cout << "d\n";

    // prepares the expressions and condition for the IfCommand / WhileCommand:

    condition = stringVector.at(2); // condition of the if or while.
    exp1String = stringVector.at(1);
    exp2String = stringVector.at(3);

    cout << "before erasing the vector\n";
    // NEED TO DELETE BEGININNG OF VECTOR ("if", conditionals... )
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());
    stringVector.erase(stringVector.begin());

    // for each command option - execute the fitting operation:
    cout << "SWITCH" << endl;
    switch (command) {

        case If : {
            cout << "It's IF man!\n";
            IfCommand ifCommand(stringVector, exp1String, exp2String, condition,
                                this->symbolTable, this->dataReaderServer, this->dataSender);
            ifCommand.execute();
            break;
        }
        case While : {
            cout << "While...." << endl;
             cout << "entered while case with1: " << exp1String << endl;
            cout <<  "entered while case with1: " << condition << endl;
            cout << "entered while case with1: " << exp2String << endl;
            WhileCommand whileCommand(stringVector, exp1String, exp2String, condition,
                                      this->symbolTable, this->dataReaderServer, this->dataSender);
            whileCommand.execute();
            break;
        }

        default:
            cout << "Before throwing..\n";
            throw "Non valid command";
    }

}
