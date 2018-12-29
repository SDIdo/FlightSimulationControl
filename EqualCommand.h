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

/**
 * This command is the "assign" command which receives a variable and
 * a value (represented by an expression or variables), and puts the calculated
 * value in fitting symbol with the symbol map.
 */

#define EQUAL_COMMAND_JUMP 3
#define SECOND_CHAR 1
#define LAST_CHAR 2
#define BUFFER_SIZE 256

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
