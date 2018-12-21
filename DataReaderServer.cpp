//
// Created by roy on 12/18/18.
//

#include "DataReaderServer.h"

void DataReaderServer::listen() {
    while (true) {
        while (alt < 1000) {
            alt += 1;
        }
    }
}

void DataReaderServer::setAlt(int newAlt) {
    this->alt = newAlt;
}