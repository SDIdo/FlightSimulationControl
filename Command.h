//
// Created by roy on 12/13/18.
//

#ifndef PROJECTPART1_COMMAND_H
#define PROJECTPART1_COMMAND_H

#include <string>

using namespace std;


class Command {

public:
    virtual int execute() = 0;
};


#endif //PROJECTPART1_COMMAND_H
