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
    cout << "[execute of Equal Command] sockfd is: " << dataSender->getSock() << "\n";
    cout << "Here with " << this->varName << "=" << this->expressionString << "\n";
    //SCAT - have to initialize dataReader first?
    if (this->dataReaderServer->isInBindMap(this->varName)) {
        cout << "[Line parser] Yep it is binded. Updating server\n";
        string address = this->dataReaderServer->getBindAddress(this->varName);

        cout << "This is the returning address of " << this->varName << " :" << address << "\n";
        cout << "A little before the shuntingYard the lexed is:\n";
        vector<string> lexed = this->smallLexer.lexer(this->expressionString);

        for (string s: lexed){
            cout << s << ", ";
        }

        double expressionValue = stod(this->util.shuntingYard(lexed));

        cout << "Wants to put in " << to_string(expressionValue) << "\n";

        this->dataReaderServer->setSymbol(address, expressionValue);

        address = address.substr(1, address.length() - 2); // cut the qoutes from the address.

        cout << "After te search\n";
        string update = " " + to_string(expressionValue);
        string updatedAddress = address + update;

        char toSend[256];
        strcpy(toSend, updatedAddress.c_str());
        cout << "[Equal Command]Show full before command: " << toSend << "\n";
        cout << "[Equal Command]Current sockfd from outside: " << this->dataSender->getSock() << endl;
        this->dataSender->sendCommand(toSend);
    } else {
        cout << "[Equal] updates the local var! \n";
        this->dataReaderServer->setSymbol(this->varName,
                                          stod(this->util.shuntingYard(
                                                  this->smallLexer.lexer(this->expressionString))));
    }
    return 3;

}