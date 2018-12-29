//
// Created by roy on 12/23/18.
//

#include "ConnectCommand.h"

using namespace std;

/**
 * Constructor of connect command, receives data sender pointer to be connected to the server.
 * @param newIp ip for the connection.
 * @param newPort port for the connection.
 * @param newDataSender data sender pointer to be connected.
 */
ConnectCommand::ConnectCommand(string newIp, string newPort, DataSender *newDataSender) {
    ip = newIp;
    port = newPort;
    dataSender = newDataSender;
}

/**
 * This method executes the connection of the data sender to the given ip and port.
 * It opens the connection with a socket.
 * @return jump for the lexer.
 */
int ConnectCommand::execute() {
    dataSender->set(ip, port);
    dataSender->openPipe(); //SCAT for now
    return JUMP_INDEX; //moves the lexer to next content
}
