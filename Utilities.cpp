#include "Utilities.h"
#include "BinaryExpression.h"
#include <stack>
#include <iostream>
#include <queue>
#include "Div.h"
#include "Mult.h"
#include "Plus.h"
#include "Minus.h"
#include "Number.h"

Utilities::Utilities() {
    operators["+"] = new Plus();
    operators["-"] = new Minus();
    operators["*"] = new Mult();
    operators["/"] = new Div();
}

void Utilities::set(SymbolTable *newSymbols) {
    symbols = newSymbols;
}

string Utilities::shuntingYard(vector<string> instream) {
    stack<string> operationStack;
    queue<string> outPutQueue;
    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it) {
        if (operators[*it] != nullptr) {
            while (!operationStack.empty() && operators[operationStack.top()] != nullptr && !precedence(*it)) {
                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }
            operationStack.push(*it);
        } else if (*it == "(") {

            operationStack.push(*it);
        } else if (*it == ")") {

            while (operationStack.top() !=
                   "(") {       //I'm tempted to think there is a need for another precedency here.

                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }

            operationStack.pop();
        } else if (isdigit((*it).at(0))) {
            operators.erase(*it);

            outPutQueue.push(*it);
        } else {
            outPutQueue.push(to_string(symbols->get(*it)));
        }
    }
    while (!operationStack.empty()) {

        outPutQueue.push(operationStack.top());
        operationStack.pop();
    }

    while (!outPutQueue.empty()) {
        std::cout << outPutQueue.front() << std::endl;
        string token = outPutQueue.front();
        outPutQueue.pop();

        if (isdigit(token.at(0))) {

            operationStack.push(token);
        } else {

            string right = operationStack.top();
            operationStack.pop();
            string left = "0";
            if (!operationStack.empty()) {
                left = operationStack.top();
                operationStack.pop();
            }

            BinaryExpression *oper = operators[token];
            oper->set(new Number(left), new Number(right));
            string sol = to_string(oper->calculate());
            operationStack.push(sol);
        }
    }
    return operationStack.top();
}

int Utilities::precedence(string currentOper) {
    if (currentOper == "+" || currentOper == "-") {
        return 0;
    }
    if (currentOper == "*" || currentOper == "/") {
        return 1;
    }
}