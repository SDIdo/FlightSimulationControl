//
// Created by idox on 12/27/18.
//

#include "FileOperation.h"

string FileOperation::readFrom(string path) {
        ifstream myfile;
        myfile.open(path); //check for error..
        if (!myfile){
            return "NULL";
        }
        string reader;
        myfile >> reader;
        myfile.close();
        return reader;
}