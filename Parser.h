//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_PARSER_H
#define PROJECTPART1_PARSER_H

#include <vector>
#include <string>
#include "CommandMap.h"

using namespace std;

class Parser {
    CommandMap commandMap;
public:
    void parse(vector<string> stringVector);
};


#endif //PROJECTPART1_PARSER_H
