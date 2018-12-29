//
// Created by roy on 12/13/18.
//

#include "OpenServerCommand.h"
#include "iostream"

using namespace std;

/**
 * Constructor of the command.
 * @param newPort given port for the server.
 * @param newHerz given times in second for the sampling.
 * @param newReader data reader server pointer for the initialization.
 * @param symbolTable symbol table pointer for the initialization.
 */
OpenServerCommand::OpenServerCommand(string newPort, string newHerz,
                                     DataReaderServer *newReader, SymbolTable *symbolTable) {
    port = newPort;
    herz = newHerz;
    dataReaderServer = newReader;
    this->symbolTable = symbolTable;
}

/**
 * This method checks if the port is valid and opens the
 * reader server with the fitting values.
 * @return jump index for the parser.
 */
int OpenServerCommand::execute() {
    // check if valid port.
    if (stod(port) < MIN_PORT || stod(port) > MAX_PORT) {
        throw "non-valid port";
    }

    dataReaderServer->set(port, herz, this->symbolTable);

    dataReaderServer->open();

    return INDEX_OPEN_SERVER_JUMP; // number of needed to move the lexer

}