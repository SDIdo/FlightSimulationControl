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

/**
 * Line parser iterates over a single line and creates the fitting
 * command out of it, then it executes the command and continues.
 */
class LineParser {
    CommandMap commandMap;
    SymbolTable* symbolTable;
    SmallLexer smallLexer;
    Utilities util;
    DataReaderServer *dataReaderServer;
    DataSender *dataSender;
public:
    int parse(vector<string> stringVector, int startIndex);
    LineParser(SymbolTable* symbolTable, DataReaderServer *dataReaderServer, DataSender * dataSender);
};


#endif //PROJECTPART1_LINEPARSER_H
