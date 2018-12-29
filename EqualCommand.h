//
// Created by roy on 12/27/18.
//

#ifndef PROJECTPART1_EQUALCOMMAND_H
#define PROJECTPART1_EQUALCOMMAND_H


#include "Command.h"
#include "DataReaderServer.h"
#include "DataSender.h"
#include "Utilities.h"
#include "SmallLexer.h"

class EqualCommand : public Command {
    string expressionString, varName;
    DataReaderServer *dataReaderServer;
    DataSender *dataSender;
    Utilities util;
    SmallLexer smallLexer;
public:
    EqualCommand(DataReaderServer *dataReaderServer, DataSender *dataSender,
            string varName, string expressionString, SymbolTable *symbolTable);

    virtual int execute();
};


#endif //PROJECTPART1_EQUALCOMMAND_H
