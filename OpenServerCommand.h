//
// Created by roy on 12/13/18.
//

#ifndef PROJECTPART1_OPENSERVERCOMMAND_H
#define PROJECTPART1_OPENSERVERCOMMAND_H


#include "Command.h"
#include <string>

using namespace std;

/**
 * This command opens a server.
 */
class OpenServerCommand : public Command {
public:
    virtual int execute(string serverArgs[]);
};


#endif //PROJECTPART1_OPENSERVERCOMMAND_H
