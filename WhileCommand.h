//
// Created by roy on 12/24/18.
//

#ifndef PROJECTPART1_WHILECOMMAND_H
#define PROJECTPART1_WHILECOMMAND_H

#include "ConditionParser.h"

class WhileCommand : public ConditionParser {
DataSender *dataSender;
public:
    WhileCommand(vector<string> commandStringVector, string exp1String, string exp2String,
            string condition, SymbolTable *symbolTablePtr, DataReaderServer *dataReaderServer, DataSender*);
    virtual int execute();
};


#endif //PROJECTPART1_WHILECOMMAND_H
