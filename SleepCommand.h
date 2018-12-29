//
// Created by roy on 12/24/18.
//

#ifndef PROJECTPART1_SLEEPCOMMAND_H
#define PROJECTPART1_SLEEPCOMMAND_H

#include<unistd.h>
#include "Command.h"

/**
 * Sleep command implements Command, therefore could be executed.
 * The execution will be sleeping the given amount of time in milliseconds.
 */

#define JUMP_SLEEP_INDEX 2
#define DIVISION_MILLISECOND 1000

class SleepCommand : public Command {
    double sleepTime;
public :
    SleepCommand(double sleepTime) {
        this->sleepTime = sleepTime;
    }

    virtual int execute() {
        sleep(this->sleepTime / DIVISION_MILLISECOND);
        return JUMP_SLEEP_INDEX;
    }
};


#endif //PROJECTPART1_SLEEPCOMMAND_H
