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
 * This command opens a server.
 */
class OpenServerCommand : public Command {
    string port;
    string herz;
    DataReaderServer* dataReaderServer;
public:
    OpenServerCommand(string, string, DataReaderServer*);
    ~OpenServerCommand() = default;
    virtual int execute();
};


#endif //PROJECTPART1_OPENSERVERCOMMAND_H
