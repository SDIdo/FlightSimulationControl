//
// Created by roy on 12/22/18.
//

#include "ConditionParser.h"

/**
 * This method return true if the condition is met, else false.
 * @return boolean - is condition met.
 */
bool ConditionParser::conditionIsMet() {
    if (this->condition == "<") {
        return this->exp1Val < this->exp2Val;
    } else if (this->condition == ">") {
        return this->exp1Val > this->exp2Val;
    } else if (this->condition == "==") {
        return this->exp1Val == this->exp2Val;
    } else if (this->condition == "!=") {
        return this->exp1Val != this->exp2Val;
    } else if (this->condition == "<=") {
        return this->exp1Val <= this->exp2Val;
    } else if (this->condition == ">=") {
        return this->exp1Val >= this->exp2Val;
    }
}