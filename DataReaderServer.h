
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

#include "BindValues.h"
#include <map>
#include <vector>


using namespace std;


class DataReaderServer {
map<string,double> strobes;     //first the address then the value
map<string, string> bindTable;  //first the address then the variable
map<string, double> symbolMap; //SCAT! for now untill I know how to pass by pointer
int sockfd = 0;
int port = 0;
int herz = 0;
public:
    DataReaderServer() = default;
    ~DataReaderServer() = default;

    void set(string, string);
    double getFromBindValues(string);
    void takeSamplesToTable(string);
    void setBind(string, string);
    void updateBindedValues();
    void open();
    void close();
    
    void setSock(int);
    int getSock();
};


#endif //PROJECTPART1_DATAREADERSERVER_H
