//
// Created by roy on 12/25/18.
//

#ifndef PROJECTPART1_VARCOMMAND_H
#define PROJECTPART1_VARCOMMAND_H

#include "Command.h"
#include "DataReaderServer.h"
#include "Utilities.h"
#include "SmallLexer.h"

class VarCommand : public Command {
    string equalSign, valueString, pathString, varName;
    DataReaderServer *dataReaderServer;
    Utilities util;
    SmallLexer smallLexer;
    SymbolTable *symbolTable;
public:
    VarCommand(DataReaderServer *dataReaderServer, SymbolTable *symbolTable, string varName, string equalSign,
               string bindString, string pathString = "");

    virtual int execute();
};


#endif //PROJECTPART1_VARCOMMAND_H
