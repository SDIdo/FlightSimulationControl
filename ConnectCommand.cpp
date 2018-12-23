/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConnectCommand.h"

using namespace std;

ConnectCommand::ConnectCommand(string newIp, string newPort, DataSender* newDataSender){
    ip = newIp;
    port = newPort;
    dataSender = newDataSender;
}

int ConnectCommand::execute(){
    dataSender->set(ip, port);
    dataSender->openPipe(); //SCAT for now
    return 3; //moves the lexer to next content
}