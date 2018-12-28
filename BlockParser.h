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
#include "Utilities.h"
#include "DataReaderServer.h"

class BlockParser {
    CommandMap commandMap;
    SymbolTable *symbolTable;
    DataReaderServer *dataReaderServer;
    SmallLexer smallLexer;
    Utilities util;
public:
    void parse(vector<string> stringVector);
    BlockParser(SymbolTable* symbolTable, DataReaderServer *dataReaderServer);
};


#endif //PROJECTPART1_BLOCKPARSER_H
