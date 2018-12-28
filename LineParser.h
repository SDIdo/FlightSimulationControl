//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_LINEPARSER_H
#define PROJECTPART1_LINEPARSER_H

#include <vector>
#include <string>
#include <iostream>
#include "CommandMap.h"
#include "SmallLexer.h"
#include "BigLexer.h"
#include "SymbolTable.h"
#include "Utilities.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "DataReaderServer.h"
#include "IfCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "VarCommand.h"
#include "EqualCommand.h"

using namespace std;

class LineParser {
    CommandMap commandMap;
    SymbolTable* symbolTable;
    SmallLexer smallLexer;
    Utilities util;
    DataReaderServer *dataReaderServer;
    DataSender dataSender;
public:
    int parse(vector<string> stringVector, int startIndex);
    LineParser(SymbolTable* symbolTable, DataReaderServer *dataReaderServer);
};


#endif //PROJECTPART1_LINEPARSER_H
