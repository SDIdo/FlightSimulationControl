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
    string address1, address2, condition, exp1String, exp2String;
    cout << "a\n";
    vector<string> valueVector1, valueVector2;
    cout << "b\n";
    string commandString = stringVector.at(0); // first string will represent the command (if/while).
    cout << "c\n";
    Commands command = commandMap.getCommand(commandString);
    cout << "d\n";

    // prepares the expressions and condition for the IfCommand / WhileCommand:

    condition = stringVector.at(2); // condition of the if or while.
    cout << "e\n";
    // calculate expression 1.
    valueVector1 = this->smallLexer.lexer(stringVector.at(1));
    cout << "f\n";
    address1 = valueVector1.at(0);
    cout << "g\n";
    if (this->dataReaderServer->isInBindMap(address1)) {
        cout << "Yeah man it's in bind map\n";
        address1 = this->dataReaderServer->getBindAddress(address1);
        valueVector1.clear();
        valueVector1.push_back(address1);
        cout << "VALUE_VECTOR: " << valueVector1.at(0) << endl;
//        sleep(2);
        cout << "Ok and what is it in the symbolTable? " << this->symbolTable->get(valueVector1.at(0));
    }
//    for (string val : valueVector1) {
//        cout << val << endl;
//    }
    cout << "Before calculating ex1\n";
    cout << "Let's see what's goingon:  " << valueVector1.at(0) << "\n";
//    cout << "Let's see what's goingon:  " << valueVector1.at(0) << "\n";
    exp1String = this->util.shuntingYard(valueVector1);
    cout << "1\n";
    // calculate expression 2.
    valueVector2 = this->smallLexer.lexer(stringVector.at(3));
    cout << "2\n";
    address2 = valueVector2.at(0);
    cout << "3\n";
    if (this->dataReaderServer->isInBindMap(address2)) {
        cout << "Yeah ex2 is in bind map!\n";
        address2 = this->dataReaderServer->getBindAddress(address2);
        cout << "4\n";
        valueVector2.clear();
        cout << "5\n";
        valueVector2.push_back(address2);
        cout << "6\n";
    }

    cout << "Before calculating exp2String to shunting yard\n";
    exp2String = this->util.shuntingYard(valueVector2);

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
