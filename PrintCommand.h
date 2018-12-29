//
// Created by roy on 12/24/18.
//

#ifndef PROJECTPART1_PRINTCOMMAND_H
#define PROJECTPART1_PRINTCOMMAND_H

#include <iostream>
#include "Command.h"

class PrintCommand : public Command {
    string printString;
public :
    PrintCommand(string printString) {
        this->printString = printString;
    }

    virtual int execute() {
        cout << this->printString << endl;
        return 2;
    }
};

#endif //PROJECTPART1_PRINTCOMMAND_H
