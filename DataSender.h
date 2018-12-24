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

class DataSender {
    char buffer[256];
    const char* ip;
    const char* port;
    int sockfd;
public:
    DataSender() = default;
    ~DataSender() = default;
    void set(string, string);
    int openPipe();
    void sendCommand(const char*);
    int getSock();
    void setSock(int newSock);
};

#endif //PROJECTPART1_DATASENDER_H
