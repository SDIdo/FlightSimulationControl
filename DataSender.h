/*
 * File:   DataSender.h
 * Author: idox
 *
 * Created on December 23, 2018, 10:57 AM
 */

#ifndef PROJECTPART1_DATASENDER_H
#define PROJECTPART1_DATASENDER_H

#include "SymbolTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <string>

using namespace std;

/**
 * This class is responsible for connection to a given IP address and port,
 * and for sending data through it.
 */

#define JUMP_INDEX 3

class DataSender {
    const char* ip;
    const char* port;
    int sockfd;
public:
    DataSender() = default;
    ~DataSender(){
        closePipe();
    }
    void set(string, string);
    int openPipe();
    void closePipe();
    void sendCommand(const char*);
    int getSock();
    void setSock(int newSock);
};

#endif //PROJECTPART1_DATASENDER_H
