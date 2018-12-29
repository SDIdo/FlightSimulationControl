#ifndef PROJECTPART1_DATAREADERSERVER_H
#define PROJECTPART1_DATAREADERSERVER_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unordered_map>
#include <vector>
#include "SymbolTable.h"
#include <thread>

using namespace std;

/**
 * Data reader server is responsible for getting strobes from the client
 * and updating bind and symbol maps (unordered maps) by the strobes received from client.
 */
class DataReaderServer {
    unordered_map<string,double> strobes;     //first the address then the value
    unordered_map<string, string> bindTable;  //first the address then the variable
    SymbolTable* symbolMap; //SCAT! for now untill I know how to pass by pointer
    int sockfd;
    int newSockFd;
    int port;
    int herz;
    bool clientAccepted;
    pthread_t myThread;
public:
    DataReaderServer() = default;
    ~DataReaderServer(){
        closeServer();
    }

    void attachThread(pthread_t);
    void set(string, string, SymbolTable*);
    bool isInBindMap(string);
    void takeSamplesToTable(string);
    void setBind(string, string);
    void setSymbol(string, double);
    string getBindAddress(string varName);
    void updateBindedValues();
    void * open();
    static void * runServer(void * a);
    void * runServerFunc(void *);
    void closeServer();

    void setSock(int);
    int getSock();
};

#endif //PROJECTPART1_DATAREADERSERVER_H
