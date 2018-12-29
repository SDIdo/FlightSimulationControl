/*
 * File:   ConnectCommand.h
 * Author: idox
 *
 * Created on December 21, 2018, 8:46 PM
 */

#ifndef PROJECTPART1_CONNECTCOMMAND_H
#define PROJECTPART1_CONNECTCOMMAND_H

#include "Command.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "DataSender.h"
#include <string.h>
using namespace std;

/**
 * Connect command execution connects a given data sender to a given ip and port.
 */

#define JUMP_INDEX 3

class ConnectCommand: public Command{ //OR command expression?
    DataSender* dataSender;
//    SymbolTable* symbolTable;
    string ip;
    string port;
public:
    ConnectCommand(string, string, DataSender*);
    ~ConnectCommand() = default;
    int virtual execute();
};

#endif //PROJECTPART1_CONNECTCOMMAND_H
