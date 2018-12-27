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
#include <map>
#include <vector>
#include "SymbolTable.h"
#include <thread>



using namespace std;

class DataReaderServer {
    map<string,double> strobes;     //first the address then the value
    map<string, string> bindTable;  //first the address then the variable
    SymbolTable symbolMap; //SCAT! for now untill I know how to pass by pointer
    int sockfd;
    int newSockFd;
    int port;
    int herz;
public:
    DataReaderServer(){
        sockfd = 0;
        newSockFd = 0;
        port = 0;
        herz = 0;
    }
    ~DataReaderServer(){
        closeSocket();
    }

    void set(string, string, SymbolTable&);
    bool isInBindMap(string);
    double getFromBindValues(string);
    void setStrobe(string bindVarName, string address);
    void takeSamplesToTable(string);
    void setBind(string, string);
    string getBindAddress(string varName);
    void updateBindedValues();
    void * open();
    static void * runServer(void * a);
    void * runServerFunc(void *);
    void setSock(int);
    int getSock();
    void closeSocket();
};

#endif //PROJECTPART1_DATAREADERSERVER_H
