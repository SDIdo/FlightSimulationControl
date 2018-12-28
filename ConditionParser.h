//
// Created by roy on 12/22/18.
//

#ifndef PROJECTPART1_CONDITIONPARSER_H
#define PROJECTPART1_CONDITIONPARSER_H

#include <vector>
#include "Command.h"
#include "SymbolTable.h"
#include "Utilities.h"
#include "SmallLexer.h"
#include "DataReaderServer.h"

class ConditionParser : public Command {
    Utilities util;
    SmallLexer smallLexer;
public:
    string condition, exp1String, exp2String;
    vector<string> commandStringVector;
    SymbolTable *symbolTablePtr;
    virtual int execute() = 0;
    virtual bool conditionIsMet();
};

#endif //PROJECTPART1_CONDITIONPARSER_H
