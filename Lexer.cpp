//
// Created by roy on 12/17/18.
//

#include "Lexer.h"
#include <string>

using namespace std;

/**
 * This function receives a string and iterates through it, inserting
 * expressions represented as strings to a string array.
 * @param str given string.
 * @return array of strings representing expressions.
 */
vector<string> Lexer::lexer(string str) {
    vector<string> stringArray;
    string currentStr;
    int i = 0;

    // iterate each char in string.
    while (i < str.length()) {

        // if whitespace or ',' - starts a new string.
        if (isspace(str.at(i)) || str.at(i) == ',') {
            if (!currentStr.empty()) {
                stringArray.push_back(currentStr);
            }
            currentStr = "";
            i++;
            continue;
        }
            // if the char is a digit - while there are more digits following it - add them to string.
        else if (isdigit(str.at(i))) {
            while (i < str.length() && (isdigit(str.at(i)) || str.at(i) == '.')) {
                currentStr += str.at(i);
                i++;
            }
            stringArray.push_back(currentStr);
            currentStr = "";
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
            currentStr += str.at(i);
            i++;
            continue;
        }
        // if the char is an operator, add it, reset the string and continue.
        else if (this->isOperator(str.at(i))) {
            currentStr += str.at(i);
            stringArray.push_back(currentStr);
            i++;
            currentStr = "";
            continue;
        }
            // if not valid.
        else
        {
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
bool Lexer::isOperator(char c) {
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
        case '=' :
            isOp = false;
            break;
        case '(' :
            isOp = true;
            break;
        case ')' :
            isOp = true;
            break;
        case '{' :
            isOp = true;
            break;
        case '}' :
            isOp = true;
            break;
        case '>' :
            isOp = true;
            break;
        case '<' :
            isOp = true;
            break;
        default:
            isOp = false;
    }
     return isOp;
}
