//
// Created by roy on 12/24/18.
//

#ifndef PROJECTPART1_SLEEPCOMMAND_H
#define PROJECTPART1_SLEEPCOMMAND_H

#include<unistd.h>
#include "Command.h"

class SleepCommand : public Command {
    double sleepTime;
public :
    SleepCommand(double sleepTime) {
        this->sleepTime = sleepTime;
    }

    virtual int execute() {
        usleep(this->sleepTime);
        return 2;
    }
};


#endif //PROJECTPART1_SLEEPCOMMAND_H
