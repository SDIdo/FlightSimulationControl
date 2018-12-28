//
// Created by roy on 12/27/18.
//

#include "FileOperation.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <string>

using namespace std;

string FileOperation::readFrom(string path) {
    string line, result;
    ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            result += line += "\n";
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    cout << result << endl;

    return result;
}