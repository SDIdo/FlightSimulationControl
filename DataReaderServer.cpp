#include "DataReaderServer.h"

/**
 * This method is responsible for setting the port and speed of information reading (hertz).
 * Also a pointer to the symbol table for both binded and unbinded variables.
 * @param newPort number of port for the connection.
 * @param newHerz number of times to read in second.
 * @param symbolTablePtr pointer to symbol table.
 */
void DataReaderServer::set(string newPort, string newHerz, SymbolTable *symbolTablePtr) {
    port = stoi(newPort);
    herz = stoi(newHerz);
    this->symbolMap = symbolTablePtr;
}

void DataReaderServer::attachThread(pthread_t newThread){
    myThread = newThread;
}

/**
 * This method checks if a given variable name is binded.
 * @param variableName variable name for the check.
 * @return bool true if in map, else false.
 */
bool DataReaderServer::isInBindMap(string subject) {
    if (bindTable.find(subject) == bindTable.end()) {
        return false;
    }
    return true;
}

/**
 * This method sets a symbol(variable) and the fitting value in the symbol map.
 * @param symbol variable name.
 * @param value value of the variable.
 */
void DataReaderServer::setSymbol(string symbol, double value) {
    this->symbolMap->set(symbol, value);
}

/**
 * This method return the bind address of a given variable.
 * @param varName name of variable.
 * @return bind address.
 */
string DataReaderServer::getBindAddress(string varName) {
    return bindTable.at(varName);
}

/**
 * This method sets a variable name and the fitting address in the bind map.
 * @param varName variable name.
 * @param address address of the binded value.
 */
void DataReaderServer::setBind(string var, string address) {
    this->bindTable[var] = address;
}

/**
 * This method sets the socket for the connection.
 * @param newSock given socket.
 */
void DataReaderServer::setSock(int newSock) {
    sockfd = newSock;
}

/**
 * This method returns the socket for the connection.
 * @return sockfd socket of the connection.
 */
int DataReaderServer::getSock() {
    return sockfd;
}

/**
 * This method updates the wanted samples (from the xml file) and updates
 * them by the samples given from the client.
 * @param sample sample for the operation.
 */
void DataReaderServer::takeSamplesToTable(string parseMe) {
    string delim = ",";
    vector<string> sol;
    //First step is to split the information
    int start = 0;
    int end = parseMe.find(delim);
    while (end != std::string::npos) {
        sol.push_back((parseMe.substr(start, end - start)));
        start = end + delim.length();
        end = parseMe.find(delim, start);
    }
    sol.push_back((parseMe.substr(start, end - start)));

    //Second step is to put that to the map//
    strobes["\"‫‪/instrumentation/airspeed-indicator/indicated-speed-kt\""] = stod(sol.at(0));
    strobes["\"/instrumentation/altimeter/indicated-altitude-ft\""] = stod(sol.at(1));
    strobes["\"‫‪/instrumentation/altimeter/pressure-alt-ft\""] = stod(sol.at(2));
    strobes["‫‪\"/instrumentation/attitude-indicator/indicated-pitch-deg\""] = stod(sol.at(3));
    strobes["\"/instrumentation/attitude-indicator/indicated-roll-deg\""] = stod(sol.at(4));
    strobes["\"/instrumentation/attitude-indicator/internal-pitch-deg\""] = stod(sol.at(5));
    strobes["\"/instrumentation/attitude-indicator/internal-roll-deg\""] = stod(sol.at(6));
    strobes["‫‪\"/instrumentation/encoder/indicated-altitude-ft\""] = stod(sol.at(7));
    strobes["‫‪\"/instrumentation/encoder/pressure-alt-ft\""] = stod(sol.at(8));
    strobes["\"/instrumentation/gps/indicated-altitude-ft\""] = stod(sol.at(9));
    strobes["\"‫‪/instrumentation/gps/indicated-ground-speed-kt\""] = stod(sol.at(10));
    strobes["\"/instrumentation/gps/indicated-vertical-speed\""] = stod(sol.at(11));
    strobes["‫‪\"/instrumentation/heading-indicator/indicated-heading-deg\""] = stod(sol.at(12));
    strobes["\"/instrumentation/heading-indicator/offset-deg\""] = stod(sol.at(13));
    strobes["‫‪\"/instrumentation/slip-skid-ball/indicated-slip-skid\""] = stod(sol.at(14));
    strobes["‫‪\"/instrumentation/turn-indicator/indicated-turn-rate\""] = stod(sol.at(15));
    strobes["‫‪\"/instrumentation/vertical-speed-indicator/indicated-speed-fpm\""] = stod(sol.at(16));
    strobes["\"/controls/flight/aileron\""] = stod(sol.at(17));
    strobes["\"/controls/flight/elevator\""] = stod(sol.at(18));
    strobes["\"/controls/flight/rudder\""] = stod(sol.at(19));
    strobes["‫‪\"/controls/flight/flaps\""] = stod(sol.at(20));
    strobes["\"/controls/engines/engine/throttle\""] = stod(sol.at(21));
    strobes["\"/engines/engine/rpm\""] = stod(sol.at(22));

}

/**
 * This method updates the symbol table according to the strobes taken from the client.
 */
void DataReaderServer::updateBindedValues() {
    for (std::unordered_map<string, double>::iterator it = strobes.begin(); it != strobes.end(); ++it) {
        // if the address of the binded variable was found in strobes, symbol table is updated:
        this->setSymbol(it->first, it->second);
    }
}

/**
 * This method opens the socket for the connection of the client.
 * Also creates pthread which then runs the server.
 */
void *DataReaderServer::open() {
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    setSock(socket(AF_INET, SOCK_STREAM, 0));

    if (getSock() < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(getSock(), (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */

    listen(getSock(), 5);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    this->newSockFd = accept(getSock(), (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (this->newSockFd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    // If connection is established then start communicating on a pthread
    pthread_create(&this->myThread, nullptr, runServer, this);
    attachThread(this->myThread);
}

/**
 * This method is used by the pthread to run the opened server.
 * @param a void pointer.
 * @return void pointer.
 */
void *DataReaderServer::runServer(void *a) {
    return ((DataReaderServer *) a)->runServerFunc(a);
}

/**
 * This method runs the server: reads information from client from
 * the socket, and updates samples map and symbol map accordingly.
 * @param a void pointer.
 * @return void pointer.
 */
void *DataReaderServer::runServerFunc(void *a) {
    int index = 0;
    int n = 0;
    char buffer[256];
    bzero(buffer, 256);
    string remainder, backRemainder, information;
    bool isDataEnd = false;

    while (true) {              //SCAT here

        n = read(this->newSockFd, buffer, 255);
        if (n < 0) {
            this->closeServer();
            pthread_exit(a);
        }
        information = string(buffer);

        if (backRemainder != "") {
            remainder = backRemainder;
            backRemainder = "";
        }

        index = information.find("\n");
        // if the line terminator was not found, append all of the information.
        if (index == std::string::npos) {
            remainder += information;
        } else {
            // appends the remainder of the information until the next line.
            remainder += information.substr(0, index);
            backRemainder = information.substr(index + 1, information.length());
            isDataEnd = true;
        }

        if (isDataEnd) {
            takeSamplesToTable(remainder);
            updateBindedValues();
            remainder = "";
            isDataEnd = false;
        }
    }
}

/**
 * This method closes the reader server.
 */
void DataReaderServer::closeServer() {
    pthread_join(myThread, nullptr);
    close(sockfd);      //SCAT no close but hightly needed!
}
