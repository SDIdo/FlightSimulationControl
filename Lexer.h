//
// Created by roy on 12/17/18.
//

#ifndef PROJECTPART1_LEXER_H
#define PROJECTPART1_LEXER_H

#include <string>
#include <vector>

using namespace std;

class Lexer {

public:
    vector<string> lexer(string);
    bool isOperator(char c);
};


#endif //PROJECTPART1_LEXER_H
