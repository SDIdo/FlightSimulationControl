//
// Created by roy on 12/13/18.
//

#include "OpenServerCommand.h"
#include <string>
#include "iostream"

using namespace std;

int OpenServerCommand::execute() {

    // check if valid port.
    if (this->port < 0 || this->port > 65535) {
        cout << "non-valid port" << endl;
        return 0;
    }
    // if valid port and rate - make server:

//    DataReaderServer

}