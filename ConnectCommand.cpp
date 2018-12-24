//
// Created by roy on 12/23/18.
//

#include "ConnectCommand.h"

using namespace std;

ConnectCommand::ConnectCommand(string newIp, string newPort, DataSender *newDataSender) {
    ip = newIp;
    port = newPort;
    dataSender = newDataSender;
}

int ConnectCommand::execute() {
    dataSender->set(ip, port);
    dataSender->openPipe(); //SCAT for now
    return 3; //moves the lexer to next content
}