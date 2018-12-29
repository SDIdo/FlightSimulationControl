//
// Created by roy on 12/23/18.
//

#include "DataSender.h"

/**
 * This method sets the IP and port of the data sender object for the connection.
 * @param newIp ip for the connection.
 * @param newPort port for the connection.
 */
void DataSender::set(string newIp, string newPort) {
    ip = newIp.c_str();
    port = newPort.c_str();
}

/**
 * This method sets the sock for the connection.
 * @param newSock sock for the connection.
 */
void DataSender::setSock(int newSock) {
    sockfd = newSock;
}

/**
 * This method returns the sock for the connection.
 * @return newSock sock for the connection.
 */
int DataSender::getSock() {
    return sockfd;
}

/**
 * This method opens the pipe for the connection for the user
 * to be able to send data.
 * @return int number of jumps in lexer.
 */
int DataSender::openPipe() {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = atoi(port);

    /* Create a socket point */
    setSock(socket(AF_INET, SOCK_STREAM, 0));

    if (getSock() < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(ip);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(getSock(), (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    return JUMP_INDEX; //num of moves in the lexer
}

/**
 * This method is used for sending commands from the user to the socket.
 * @param buffer command to be sent to the socket.
 */
void DataSender::sendCommand(const char buffer[256]) {

    /* Now ask for a message from the user, this message
     * will be read by server
     */
    char myBuffer[256];
    bzero(myBuffer, 256);
    memcpy(myBuffer, buffer, 256);
    int n = 0;
    char setString[256] = {'s', 'e', 't', ' '};
    strcat(setString, myBuffer);
    strcat(setString, "\r\n");

    /* Send message to the server */
    n = write(getSock(), setString, strlen(setString));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now read server response */
    bzero(myBuffer, 256);
    n = read(getSock(), myBuffer, 256);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
}

/**
 * This method is used for closing the communication socket.
 */
void DataSender::closePipe(){
    close(sockfd);
}