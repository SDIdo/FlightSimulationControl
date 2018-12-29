//
// Created by roy on 12/25/18.
//

#include <iostream>
#include "VarCommand.h"

/**
 * Constructor of the command.
 * @param dataReaderServer data reader server for checks in the bind map.
 * @param symbolTable symbol table for the values.
 * @param varName name of the given var for the update.
 * @param equalSign the sign of assigning operation.
 * @param valueString value of the string.
 * @param pathString path of the string (if it needs to be binded).
 */
VarCommand::VarCommand(DataReaderServer *dataReaderServer, SymbolTable *symbolTable, string varName, string equalSign,
                       string valueString, string pathString) {
    this->varName = varName;
    this->equalSign = equalSign;
    this->valueString = valueString;
    this->pathString = pathString;
    this->dataReaderServer = dataReaderServer;
    this->symbolTable = symbolTable;
    this->util.set(symbolTable, this->dataReaderServer);
}

/**
 * This method executes the operation of the assignment.
 * @return jump index for the parser.
 */
int VarCommand::execute() {
    // if the command was bind: (like var break = bind "/controls/flight/fastbreaks" ")
    if ((this->equalSign == "=") && (this->valueString == "bind")) {
        this->dataReaderServer->setBind(this->varName, this->pathString);
        return BINDED_JUMP_INDEX;
    }
        // else, the variable is a local variable, and not binded var: (like "var breaks = 0")
    else {
        string address;
        vector<string> valueVector = this->smallLexer.lexer(this->valueString);
        address = valueVector.at(0);
        if (this->dataReaderServer->isInBindMap(address)) {
            address = this->dataReaderServer->getBindAddress(address);
            valueVector.clear();
            valueVector.push_back(address);
        }
        string expressionAfterEquation = this->util.shuntingYard(valueVector);
        this->dataReaderServer->setSymbol(this->varName, stod(expressionAfterEquation));
        return UNBINDED_JUMP_INDEX;
    }
}