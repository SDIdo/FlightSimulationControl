//
// Created by roy on 12/22/18.
//

#include "ConditionParser.h"

/**
 * This method return true if the condition is met, else false.
 * @return boolean - is condition met.
 */
bool ConditionParser::conditionIsMet() {
    vector<string> valueVector1, valueVector2;
    string address1, address2;
    double value1, value2;
    valueVector1 = this->smallLexer.lexer(this->exp1String);
    address1 = valueVector1.at(0);
    if (this->dataReaderServer->isInBindMap(address1)) {
        address1 = this->dataReaderServer->getBindAddress(address1);
        valueVector1.clear();
        valueVector1.push_back(address1);

    }
    value1 = stod(this->util.shuntingYard(valueVector1));

    // calculate expression 2.
    valueVector2 = this->smallLexer.lexer(this->exp2String);
    address2 = valueVector2.at(0);
    if (this->dataReaderServer->isInBindMap(address2)) {
        address2 = this->dataReaderServer->getBindAddress(address2);
        valueVector2.clear();
        valueVector2.push_back(address2);
    }
    value2 = stod(this->util.shuntingYard(valueVector2));

    if (this->condition == "<") {
        return value1 < value2;
    } else if (this->condition == ">") {
        return value1 > value2;
    } else if (this->condition == "==") {
        return value1 == value2;
    } else if (this->condition == "!=") {
        return value1 != value2;
    } else if (this->condition == "<=") {
        return value1 <= value2;
    } else if (this->condition == ">=") {
        return value1 >= value2;
    }
}