//
// Created by roy on 12/18/18.
//

#include "BigLexer.h"

/**
* This function receives a string and iterates through it, inserting
* expressions represented as strings to a string array.
* @param str given string.
* @return array of strings representing expressions.
*/
vector<string> BigLexer::lexer(string str) {
    vector<string> stringArray;
    string currentStr;
    bool validExpEnd = false, isNumBracket = false, alphaBetExpression = false;
    int i = 0;

    // iterate each char in string.
    while (i < str.length()) {

        // if ',' starts a new string.
        if (str.at(i) == ',') {
            if (!currentStr.empty()) {
                stringArray.push_back(currentStr);
            }
            currentStr = "";
            i++;
            continue;
        }
            // if the char is a digit, or expression operation:
        else if (isdigit(str.at(i)) || isExpOperator(str.at(i))) {

            // if reached an end of alphabetic expression, adds it to the vector and creates new string.
            if (alphaBetExpression) {
                stringArray.push_back(currentStr);
                currentStr = "";
                alphaBetExpression = false;
            }

            // if a new expression - push current string to array and start new one.
            if (validExpEnd && (isdigit(str.at(i)) || str.at(i) == '(')) {
                stringArray.push_back(currentStr);
                currentStr = "";
            }
            validExpEnd = false; // the current string is no longer a valid expression.

            // while current char is digit, dot, or valid expression operator, adds to curr str.
            while (i < str.length() && (isdigit(str.at(i)) || str.at(i) == '.' || isExpOperator(str.at(i)))) {

                validExpEnd = isdigit(str.at(i)) || str.at(i) == ')';
                currentStr += str.at(i);
                i++;
            }
            continue;
        }
            // if the char is " (double quotes = beginning of a string) - add chars until next ".
        else if (str.at(i) == '"') {
            currentStr += str.at(i);
            i++;
            while (i < str.length() && str.at(i) != '"') {
                currentStr += str.at(i);
                i++;
            }
            currentStr += str.at(i);
            stringArray.push_back(currentStr);
            i++;
            currentStr = "";
            continue;
        }

            // if the char is of the alphabet, add it and continue.
        else if (isalpha(str.at(i))) {
            if (validExpEnd) {
                stringArray.push_back(currentStr);
                currentStr = "";
                validExpEnd = false;
            }

            alphaBetExpression = true;
            currentStr += str.at(i);
            i++;
            continue;
        }
            // if the char is '}','{','=','<','>' add to vector and continue with new string.
        else if (str.at(i) == '}' || str.at(i) == '{' || str.at(i) == '=' || str.at(i) == '<' ||
                 str.at(i) == '>') {
            if (!currentStr.empty()) {
                stringArray.push_back(currentStr);
            }
            currentStr = "";
            currentStr += str.at(i);
            stringArray.push_back(currentStr);
            currentStr = "";
            i++;
        }

            // if not valid char, skip to next.
        else {
            i++;
        }
    }

    if (!currentStr.empty()) {
        stringArray.push_back(currentStr);
    }

    return stringArray;

}


/**
* This method checks if a char is a valid operator.
* @param c given char.
* @return boolean - true if c is an operator, else false.
*/
bool BigLexer::isExpOperator(char c) {
    bool isOp;
    switch (c) {
        case '+' :
            isOp = true;
            break;
        case '-' :
            isOp = true;
            break;
        case '*' :
            isOp = true;
            break;
        case '/' :
            isOp = true;
            break;
        case '(' :
            isOp = true;
            break;
        case ')' :
            isOp = true;
            break;
            // if not operator, isOp = false.
        default:
            isOp = false;
    }
    return isOp;
}