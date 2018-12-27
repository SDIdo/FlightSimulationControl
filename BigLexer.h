//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_BIGLEXER_H
#define PROJECTPART1_BIGLEXER_H

#include "Lexer.h"

class BigLexer : public Lexer{
    bool isExpOperator(char c);
public:
    virtual vector<string> lexer(string);
};


#endif //PROJECTPART1_BIGLEXER_H
