/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectCommand.h
 * Author: idox
 *
 * Created on December 21, 2018, 8:46 PM
 */

#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H
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

#endif /* CONNECTCOMMAND_H */

