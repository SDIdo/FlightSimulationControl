//
// Created by roy on 12/17/18.
//

#ifndef PROJECTPART1_SMALLLEXER_H
#define PROJECTPART1_SMALLLEXER_H

#include "Lexer.h"

class SmallLexer : public Lexer {
    bool isOperator(char c);
public:
    virtual vector<string> lexer(string);
};


#endif //PROJECTPART1_LEXER_H
