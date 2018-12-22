//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_CONDITIONPARSER_H
#define PROJECTPART1_CONDITIONPARSER_H

#include <vector>
#include "Command.h"
#include "SymbolTable.h"

class ConditionParser : public Command {
public:
    string condition;
    double exp1Val, exp2Val;
    vector<string> commandStringVector;
    SymbolTable *symbolTablePtr;
    virtual int execute() = 0;
    virtual bool conditionIsMet();
};

#endif //PROJECTPART1_CONDITIONPARSER_H
