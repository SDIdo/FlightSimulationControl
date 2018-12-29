//
// Created by roy on 12/27/18.
//

#include "EqualCommand.h"

EqualCommand::EqualCommand(DataReaderServer *dataReaderServer, DataSender *dataSender,
                           string varName, string expressionString, SymbolTable *symbolTable) {
    this->dataReaderServer = dataReaderServer;
    this->dataSender = dataSender;
    this->varName = varName;
    this->expressionString = expressionString;
    this->util.set(symbolTable, this->dataReaderServer);
}

int EqualCommand::execute() {

    if (this->dataReaderServer->isInBindMap(this->varName)) {

        string address = this->dataReaderServer->getBindAddress(this->varName);

        vector<string> lexed = this->smallLexer.lexer(this->expressionString);

        double expressionValue = stod(this->util.shuntingYard(lexed));


        this->dataReaderServer->setSymbol(address, expressionValue);

        address = address.substr(1, address.length() - 2); // cut the qoutes from the address.
        string update = " " + to_string(expressionValue);
        string updatedAddress = address + update;

        char toSend[256];
        strcpy(toSend, updatedAddress.c_str());
        this->dataSender->sendCommand(toSend);
    } else {
        this->dataReaderServer->setSymbol(this->varName,
                                          stod(this->util.shuntingYard(
                                                  this->smallLexer.lexer(this->expressionString))));
    }
    return 3;

}