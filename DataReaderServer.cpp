
#include "DataReaderServer.h"


void DataReaderServer::set(string newPort, string newHerz){
    port = stoi(newPort);
    herz = stoi(newHerz);
}

double DataReaderServer::getFromBindValues(string bindVal){
    return strobes.at(bindVal);
}

void DataReaderServer::setSock(int newSock){
    sockfd = newSock;
}

int DataReaderServer::getSock(){
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
    strobes["‫‪/controls/flight/rudder‬‬"] = stod(sol.at(20));
    
    
    //ETC.. add all the addresses ...
    
    
    
//    cout << "Lets see for example the rudder.." << strobes.at("‫‪/controls/flight/rudder‬‬") << "\n";
//    printf("Done managing the rudder which is now.. %d\n", stod(strobes.at("‫‪/controls/flight/rudder‬‬")));
}

void DataReaderServer::updateBindedValues(){
    cout << "[Update binded values] Welcome to check and update\n";
    for (std::map<string, string>::iterator it = bindTable.begin(); it != bindTable.end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
        if (strobes[bindTable[it->first]] != 0){
            cout << "Ok! there's a bineded value! Update it's symbolTable\n which is: " << it->first << endl;
            symbolMap[it->first] = strobes[bindTable[it->first]];
        }
        else{
            strobes.erase(it->first);
        }
    }
        
}

void DataReaderServer::setBind(string var, string address){
    cout << "New var is binded as such: " << var << " = " << address << "\n";
    bindTable[var] = address;
}
void DataReaderServer::open() {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* First call to socket() function */
    setSock(socket(AF_INET, SOCK_STREAM, 0));

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(getSock(), (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */

    listen(getSock(), 5);
    clilen = sizeof (cli_addr);
    printf("Waiting for a client\n");
    /* Accept actual connection from the client */
    newsockfd = accept(getSock(), (struct sockaddr *) &cli_addr, (socklen_t*) & clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    printf("Ever Listening..\n");       //SCAT! here you get array of information that updates the map..
    /* If connection is established then start communicating */
    while (true) {              //SCAT here
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        
        printf("Information from simulator: %s\n", buffer);
        string information = buffer;
        
        
        takeSamplesToTable(information);   //receive and update local map.
        updateBindedValues();
        
        
//        printf("Got it : %c\n", information.substr(i, i = information.find(",")));
//        while()
//        strobes[]

        /* Write a response to the client */
//        n = write(newsockfd, "I got your message\n", 19);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
}
void DataReaderServer::close(){
//    close();      //SCAT no close but hightly needed!
}