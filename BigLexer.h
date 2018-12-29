//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_BIGLEXER_H
#define PROJECTPART1_BIGLEXER_H

#include "Lexer.h"

/**
* Class BigLexer is responsible for inserting expressions represented
* as strings to a string array.
* @param str given string.
* @return array of strings representing expressions.
*/

class BigLexer : public Lexer{
    bool isExpOperator(char c);
public:
    virtual vector<string> lexer(string);
};


#endif //PROJECTPART1_BIGLEXER_H
