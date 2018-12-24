//
// Created by roy on 12/13/18.
//

#include "OpenServerCommand.h"
#include <string>
#include "iostream"

using namespace std;

OpenServerCommand::OpenServerCommand(string newPort, string newHerz,
                                     DataReaderServer *newReader, SymbolTable *symbolTable) {
    port = newPort;
    herz = newHerz;
    dataReaderServer = newReader;
    this->symbolTable = symbolTable;
}

int OpenServerCommand::execute() {
    // check if valid port.
    if (stod(port) < 0 || stod(port) > 65535) {
        cout << "non-valid port" << endl;
        return 0;
    }
    cout << "[Opening a server] We are here" << "\n";

    dataReaderServer->set(port, herz, this->symbolTable);
    cout << "[Opening a server] Done initializing\n";

    dataReaderServer->open();

    return 3; // number of needed to move the lexer

}