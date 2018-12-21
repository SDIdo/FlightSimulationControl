//
// Created by roy on 12/13/18.
//

#ifndef PROJECTPART1_OPENSERVERCOMMAND_H
#define PROJECTPART1_OPENSERVERCOMMAND_H


#include "Command.h"
#include <string>
#include <vector>

using namespace std;

/**
 * This command opens a server.
 */
class OpenServerCommand : public Command {
    int port, hertz;
public:
    OpenServerCommand(int port, int hertz) {
        this->port = port;
        this->hertz = hertz;
    }
    virtual int execute();
};


#endif //PROJECTPART1_OPENSERVERCOMMAND_H
