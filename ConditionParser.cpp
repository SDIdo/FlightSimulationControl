//
// Created by roy on 12/22/18.
//

#include "ConditionParser.h"

/**
 * This method return true if the condition is met, else false.
 * @return boolean - is condition met.
 */
bool ConditionParser::conditionIsMet() {
    double exp1Val = stod(this->exp1String);
    double exp2Val = stod(this->exp2String);
    if (this->condition == "<") {
        return exp1Val < exp2Val;
    } else if (this->condition == ">") {
        return exp1Val > exp2Val;
    } else if (this->condition == "==") {
        return exp1Val == exp2Val;
    } else if (this->condition == "!=") {
        return exp1Val != exp2Val;
    } else if (this->condition == "<=") {
        return exp1Val <= exp2Val;
    } else if (this->condition == ">=") {
        return exp1Val >= exp2Val;
    }
}