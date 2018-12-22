//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_IFCOMMAND_H
#define PROJECTPART1_IFCOMMAND_H


#include "ConditionParser.h"

class IfCommand : public ConditionParser {

public:
    IfCommand(vector<string> commandStringVector, double exp1Val, double exp2Val,
            string condition, SymbolTable *symbolTablePtr);
    virtual int execute();
};


#endif //PROJECTPART1_IFCOMMAND_H
