//
// Created by roy on 12/24/18.
//

#ifndef PROJECTPART1_PRINTCOMMAND_H
#define PROJECTPART1_PRINTCOMMAND_H

#include <iostream>
#include "Command.h"

/**
 * Class print command implements Command, therefore could be executed.
 * The execution of this command prints given string to the screen.
 */

#define JUMP_PRINT_INDEX 2

class PrintCommand : public Command {
    string printString;
public :
    PrintCommand(string printString) {
        this->printString = printString;
    }

    virtual int execute() {
        cout << this->printString << endl;
        return JUMP_PRINT_INDEX;
    }
};

#endif //PROJECTPART1_PRINTCOMMAND_H
