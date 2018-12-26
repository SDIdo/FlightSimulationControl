#include "DataReaderServer.h"


void DataReaderServer::set(string newPort, string newHerz, SymbolTable *symbolTablePtr) {
    cout << "start to set things.. " << stoi(newPort) << ", " << newHerz << "\n";
    cout << "Before port is " << port << "\n";
    port = stoi(newPort);
    cout << "Then port is " << port << "\n";
    herz = stoi(newHerz);
    cout << "Done setting things\n";
    this->symbolMap = symbolTablePtr;
}

bool DataReaderServer::isInBindMap(string subject) {
    cout << "[DataReaderServer] Looking through bind map\n";
//    cout << bindTable << endl;
    if (bindTable.find(subject) == bindTable.end()) {
        cout << "Wasn't found!\n";
        return false;
    }
    return true;
}

double DataReaderServer::getFromBindValues(string bindVal) {
    cout << "[DataReader] Looking through the binds...\n";
    return strobes.at(bindVal);
}

string DataReaderServer::getBindAddress(string varName) {
    cout << "[DataReader] Looking through the binds...\n";
    return bindTable.at(varName);
}

void DataReaderServer::setSock(int newSock) {
    sockfd = newSock;
}

int DataReaderServer::getSock() {
    return sockfd;
}

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
    strobes["\"‫‪/instrumentation/attitude-indicator/indicated-roll-deg\""] = stod(sol.at(4));
    strobes["‫\"/instrumentation/attitude-indicator/internal-pitch-deg\""] = stod(sol.at(5));
    strobes["\"/instrumentation/attitude-indicator/internal-roll-deg\""] = stod(sol.at(6));
    strobes["‫‪\"/instrumentation/encoder/indicated-altitude-ft\""] = stod(sol.at(7));
    strobes["‫‪\"/instrumentation/encoder/pressure-alt-ft\""] = stod(sol.at(8));
    strobes["\"/instrumentation/gps/indicated-altitude-ft\""] = stod(sol.at(9));
    strobes["\"‫‪/instrumentation/gps/indicated-ground-speed-kt\""] = stod(sol.at(10));
    strobes["‫\"/instrumentation/gps/indicated-vertical-speed\""] = stod(sol.at(11));
    strobes["‫‪\"/instrumentation/heading-indicator/indicated-heading-deg\""] = stod(sol.at(12));
    strobes["\"/instrumentation/magnetic-compass/indicated-heading-deg\""] = stod(sol.at(13));
    strobes["‫‪\"/instrumentation/slip-skid-ball/indicated-slip-skid\""] = stod(sol.at(14));
    strobes["‫‪\"/instrumentation/turn-indicator/indicated-turn-rate\""] = stod(sol.at(15));
    strobes["‫‪\"/instrumentation/vertical-speed-indicator/indicated-speed-fpm\""] = stod(sol.at(16));
    strobes["\"/controls/flight/ailero\""] = stod(sol.at(17));
    strobes["\"/controls/flight/elevator\""] = stod(sol.at(18));
    strobes["A"] = stod(sol.at(19));

    cout << "and current A (rudder) is " << strobes["A"] << "\n";

    strobes["‫‪\"/controls/flight/flaps\""] = stod(sol.at(20));
    strobes["‫\"/controls/engines/current-engine/throttle\""] = stod(sol.at(21));
    strobes["‫‪\"/engines/engine/rpm\""] = stod(sol.at(22));


    //ETC.. add all the addresses ...



//    cout << "Lets see for example the rudder.." << strobes.at("‫‪/controls/flight/rudder‬‬") << "\n";
//    printf("Done managing the rudder which is now.. %d\n", stod(strobes.at("‫‪/controls/flight/rudder‬‬")));
}

void DataReaderServer::updateBindedValues() {
    cout << "size of bind table is " << bindTable.size() << endl;
    cout << "[Update binded values] Welcome to check and update\n";
    for (std::map<string, string>::iterator it = bindTable.begin(); it != bindTable.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
        if (strobes[it->second] != 0) { // THIS CHECK - IS IT GOOD?
            cout << "Ok! there's a bineded value! Update it's symbolTable\n which is: " << it->first << endl;
            symbolMap->set(it->first, strobes[bindTable[it->first]]);
        } else {
            strobes.erase(bindTable[it->first]);
            bindTable.erase(it->first);
            cout << "HE WANTED TO ERASE ME" << it->first << endl;
        }
    }
}

void DataReaderServer::setBind(string var, string address) {
    cout << "New var is binded as such: " << var << " = " << address << "\n";
    this->bindTable[var] = address;
}

void *DataReaderServer::open() {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    setSock(socket(AF_INET, SOCK_STREAM, 0));

    if (sockfd < 0) {
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
    printf("Waiting for a client\n");
    /* Accept actual connection from the client */
    this->newSockFd = accept(getSock(), (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    printf("socket was created!\n");
    if (this->newSockFd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    printf("Ever Listening..\n");       //SCAT! here you get array of information that updates the map..
    /* If connection is established then start communicating on a pthread */

    pthread_t t1ID;
    pthread_create(&t1ID, nullptr, runServer, this);
}

void *DataReaderServer::runServer(void *a) {
    return ((DataReaderServer *) a)->runServerFunc(a);
}

void *DataReaderServer::runServerFunc(void *a) {
    int lastPos = 0;
    int count = 0;
    int n, index = 0;
    char buffer[256];
    string information;
    string remainder, backRemainder;
    bool isDataEnd = false;

    while (true) {              //SCAT here

        sleep(5);

        bzero(buffer, 256);
        n = read(this->newSockFd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        information = string(buffer);

        if (backRemainder != "") {
            remainder = backRemainder;
            backRemainder = "";
        }

        int index = information.find("\n");
        // if the new line was not found yet, append all of the information.
        if (index == std::string::npos) {
            remainder += information;
        } else {
            // appends the remainder of the information until the next line.
            remainder += information.substr(0, index);
            backRemainder = information.substr(index +1, information.length());
            isDataEnd = true;
        }

        if (isDataEnd) {
            cout << "Information from simulator: " << remainder.length() << "and the data: " << remainder << "\n";
            takeSamplesToTable(remainder);   //receive and update local map.
            updateBindedValues();
            remainder = "";
            isDataEnd = false;
        }

//        printf("Got it : %c\n", information.substr(i, i = information.find(",")));
//        while()
//        strobes[]

/* Write a response to the client */
//        n = write(newsockfd, "I got your message\n", 19);
//        if (n < 0) {
//            perror("ERROR writing to socket");
//            exit(1);
//        }
    }
}

void DataReaderServer::close() {
//    close();      //SCAT no close but hightly needed!
}















/**
THis is try */

//while (index < information.length()) {
//index = information.find(",");
//// if the new line was not found yet, append all of the information.
//if (index == std::string::npos) {
//remainder += information.substr(lastPos, information.length());
//} else {
//// appends the remainder of the information until the next line.
//remainder += information.substr(0, index);
//lastPos = index + 1;
//count++;
//}
//}
//// if done with delimeters, valid input.
//if (count == 22) {
//cout << "Length of clean input: " << remainder.length() << "and the data: " << remainder << "\n";
////            takeSamplesToTable(remainder);   //receive and update local map.
////            updateBindedValues();
//remainder = "";
//index = 0;
//lastPos = 0;
//count = 0;
//}