//
// Created by roy on 12/23/18.
//

#include "DataSender.h"

void DataSender::set(string newIp, string newPort) { //staticate for now.. but should be a vector..
    ip = newIp.c_str();
    port = newPort.c_str();
}

void DataSender::setSock(int newSock) {
    sockfd = newSock;
}

int DataSender::getSock() {
    return sockfd;
}

int DataSender::openPipe() {
    cout << "[open pipe properties] ip = " << ip << " and port = " << port << "\n";
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    //
    //    char buffer[256];
    //
    //    if (argc < 3) {
    //        fprintf(stderr, "usage %s hostname port\n", argv[0]);
    //        exit(0);
    //    }

    portno = atoi(port);

    /* Create a socket point */
    setSock(socket(AF_INET, SOCK_STREAM, 0));

    printf("[From Connection] sockfd is %d\n", getSock());

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
    return 3; //num of moves in the lexer
}

void DataSender::sendCommand(const char buffer[256]) {

    /* Now ask for a message from the user, this message
     * will be read by server
     */
    printf("Currently sockfd is set to %d\n", getSock());
    char myBuffer[256];
    bzero(myBuffer, 256);
    memcpy(myBuffer, buffer, 256);
    int n = 0;
    char setString[256] = {'s', 'e', 't', ' '};
    strcat(setString, myBuffer);
    printf("Current msg to send: %s\n", setString);
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

    printf("That was sent: %s\n", myBuffer);
}