//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_IFCOMMAND_H
#define PROJECTPART1_IFCOMMAND_H


#include "ConditionParser.h"

class IfCommand : public ConditionParser {
DataSender *dataSender;
public:
    IfCommand(vector<string> commandStringVector, string exp1String, string exp2String,
            string condition, SymbolTable *symbolTablePtr, DataReaderServer *dataReaderServer, DataSender*);
    virtual int execute();
};


#endif //PROJECTPART1_IFCOMMAND_H
