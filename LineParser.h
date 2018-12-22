//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_LINEPARSER_H
#define PROJECTPART1_LINEPARSER_H

#include <vector>
#include <string>
#include "CommandMap.h"
#include "SmallLexer.h"
#include "BigLexer.h"
#include "SymbolTable.h"


using namespace std;

class LineParser {
    CommandMap commandMap;
    SymbolTable* symbolTable;
    SmallLexer smallLexer;
public:
    void parse(vector<string> stringVector);
    LineParser(SymbolTable* symbolTable);
};


#endif //PROJECTPART1_LINEPARSER_H
