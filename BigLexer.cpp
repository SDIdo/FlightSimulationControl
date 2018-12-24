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
    bool validExpEnd = false, isNumBracket = false, alphabetChar = false, validAlphaExp = false;
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
            if (alphabetChar || validAlphaExp) {
                if (!(str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '/' || str.at(i) == '*')) {
                    stringArray.push_back(currentStr);
                    currentStr = "";
                }
                alphabetChar = false;
                validAlphaExp = false;
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
            // if there was any string, puts into vector and resets current string.
            if (!currentStr.empty()) {
                stringArray.push_back(currentStr);
                currentStr = "";
                validExpEnd = false;
                validAlphaExp = false;
            }
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

            // if the char is of the alphabet.
        else if (isalpha(str.at(i))) {
            // if the current string is a valid expression, push to vector and reset string.
            if (validExpEnd || validAlphaExp) {
                stringArray.push_back(currentStr);
                currentStr = "";
                validExpEnd = false;
                validAlphaExp = false;
            }
            alphabetChar = true;
            currentStr += str.at(i);
            i++;
            continue;
        }
            // if the char is '}','{','=','<','>' add to vector and continue with new string.
        else if (str.at(i) == '}' || str.at(i) == '{' || str.at(i) == '=' ||
                 str.at(i) == '<' || str.at(i) == '>' || str.at(i) == '!') {
            if (!currentStr.empty()) {
                stringArray.push_back(currentStr);
                alphabetChar = false;
                validExpEnd = false;
                validAlphaExp = false;
                currentStr = "";
            }
            currentStr += str.at(i);
            // if the condition is a 2 char condition, add the next char also.
            if (((str.at(i) == '<' || str.at(i) == '>') && str.at(i + 1) == '=') ||
                ((str.at(i) == '!' || str.at(i) == '=') && str.at(i + 1) == '=')) {
                currentStr += str.at(i + 1);
            }
            stringArray.push_back(currentStr);
            currentStr = "";
            i++;
            continue;
        }
            // if the current char is whitespace.
        else if (isspace(str.at(i)) && alphabetChar) {
            // if there is a valid alphabetic expression, add to vector and reset string.
            alphabetChar = false;
            validAlphaExp = true;
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