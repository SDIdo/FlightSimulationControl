//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_LEXER_H
#define PROJECTPART1_LEXER_H

#include <string>
#include <vector>

using namespace std;

/**
 * Interface Lexer.
 */
class Lexer {
public:
    virtual vector<string> lexer(string) = 0;
};

#endif //PROJECTPART1_LEXER_H
