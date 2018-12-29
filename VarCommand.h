//
// Created by roy on 12/25/18.
//

#ifndef PROJECTPART1_VARCOMMAND_H
#define PROJECTPART1_VARCOMMAND_H

#include "Command.h"
#include "DataReaderServer.h"
#include "Utilities.h"
#include "SmallLexer.h"

/**
 * VarCommand implements Command, therefore could be executed.
 * The execution of the command will create a new variable and
 * update the relevant maps.
 */

#define BINDED_JUMP_INDEX 5
#define UNBINDED_JUMP_INDEX 4

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
