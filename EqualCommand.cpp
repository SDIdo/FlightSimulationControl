//
// Created by roy on 12/27/18.
//

#include "EqualCommand.h"

/**
 * Constructor of the command.
 * @param dataReaderServer data reader server for the checks in the binded variables table.
 * @param dataSender data sender for sending the data to the simulator if needed.
 * @param varName name of the var for the assigning.
 * @param expressionString string of the expression to be calculated.
 * @param symbolTable symbol table for the values.
 */
EqualCommand::EqualCommand(DataReaderServer *dataReaderServer, DataSender *dataSender,
                           string varName, string expressionString, SymbolTable *symbolTable) {
    this->dataReaderServer = dataReaderServer;
    this->dataSender = dataSender;
    this->varName = varName;
    this->expressionString = expressionString;
    this->util.set(symbolTable, this->dataReaderServer);
}

/**
 * This method executes the assigning operation.
 * @return value for the jump with lexer.
 */
int EqualCommand::execute() {

    if (this->dataReaderServer->isInBindMap(this->varName)) {

        string address = this->dataReaderServer->getBindAddress(this->varName);

        vector<string> lexed = this->smallLexer.lexer(this->expressionString);

        double expressionValue = stod(this->util.shuntingYard(lexed));


        this->dataReaderServer->setSymbol(address, expressionValue);

        address = address.substr(SECOND_CHAR, address.length() - LAST_CHAR); // cut the qoutes from the address.
        string update = " " + to_string(expressionValue);
        string updatedAddress = address + update;

        char toSend[BUFFER_SIZE];
        strcpy(toSend, updatedAddress.c_str());
        this->dataSender->sendCommand(toSend);
    } else {
        this->dataReaderServer->setSymbol(this->varName,
                                          stod(this->util.shuntingYard(
                                                  this->smallLexer.lexer(this->expressionString))));
    }
    return EQUAL_COMMAND_JUMP;

}