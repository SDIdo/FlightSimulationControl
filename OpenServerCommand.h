//
// Created by roy on 12/13/18.
//

#ifndef PROJECTPART1_OPENSERVERCOMMAND_H
#define PROJECTPART1_OPENSERVERCOMMAND_H


#include "Command.h"
#include <string>
#include <vector>
#include "DataReaderServer.h"

using namespace std;

/**
 * Open server command implements command, therefore can be executed.
 * The execution of the command opens a server with given port and hertz.
 */

#define MAX_PORT 65535
#define MIN_PORT 0
#define INDEX_OPEN_SERVER_JUMP 3

class OpenServerCommand : public Command {
    string port;
    string herz;
    DataReaderServer *dataReaderServer;
    SymbolTable *symbolTable;
public:
    OpenServerCommand(string, string, DataReaderServer *, SymbolTable*);
    ~OpenServerCommand() = default;
    virtual int execute();
};


#endif //PROJECTPART1_OPENSERVERCOMMAND_H
