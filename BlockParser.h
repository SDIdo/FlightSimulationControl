//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_BLOCKPARSER_H
#define PROJECTPART1_BLOCKPARSER_H

#include <vector>
#include <string>
#include "CommandMap.h"
#include "SmallLexer.h"
#include "BigLexer.h"
#include "SymbolTable.h"

class BlockParser {
    CommandMap commandMap;
    SymbolTable *symbolTable;
    SmallLexer smallLexer;
    BigLexer bigLexer;
public:
    void parse(vector<string> stringVector);
    BlockParser(SymbolTable* symbolTable);
};


#endif //PROJECTPART1_BLOCKPARSER_H
