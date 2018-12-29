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
    cout << "f\n";
    address1 = valueVector1.at(0);
    cout << "g\n";
    if (this->dataReaderServer->isInBindMap(address1)) {
        cout << "Yeah man it's in bind map\n";
        address1 = this->dataReaderServer->getBindAddress(address1);
        valueVector1.clear();
        valueVector1.push_back(address1);
        cout << "VALUE_VECTOR: " << valueVector1.at(0) << endl;

    }
    cout << "Before calculating ex1\n";
    cout << "Let's see what's goingon:  " << valueVector1.at(0) << "\n";
//    cout << "Let's see what's goingon:  " << valueVector1.at(0) << "\n";
    value1 = stod(this->util.shuntingYard(valueVector1));

    // calculate expression 2.
    valueVector2 = this->smallLexer.lexer(this->exp2String);
    cout << "2\n";
    address2 = valueVector2.at(0);
    cout << "3\n";
    if (this->dataReaderServer->isInBindMap(address2)) {
        cout << "Yeah ex2 is in bind map!\n";
        address2 = this->dataReaderServer->getBindAddress(address2);
        cout << "4\n";
        valueVector2.clear();
        cout << "5\n";
        valueVector2.push_back(address2);
        cout << "6\n";
    }
    cout << "Before calculating exp2String to shunting yard\n";
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