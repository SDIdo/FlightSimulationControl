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

Utilities::~Utilities(){
    for (std::unordered_map<string,BinaryExpression*>::iterator it=operators.begin(); it!=operators.end(); ++it) {
        delete(it->second);
    }
}

void Utilities::set(SymbolTable *newSymbols, DataReaderServer * newDataServer) {
    symbols = newSymbols;
    dataServer = newDataServer;
}


string Utilities::shuntingYard(vector<string> instream) {
    stack<string> operationStack;
    queue<string> outPutQueue;
    string left;
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
                   "(") {

                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }

            operationStack.pop();
            //number situation
        } else if (isdigit((*it).at(0))) {
            operators.erase(*it);

            outPutQueue.push(*it);
            //variable situation
        } else if (this->dataServer->isInBindMap(*it)){
            string address = this->dataServer->getBindAddress(*it);
            double value = this->symbols->get(address);
            outPutQueue.push(to_string(value));
        }
        else {
            outPutQueue.push(to_string(symbols->get(*it)));
        }
    }

    //Second Stage//
    while (!operationStack.empty()) {
        outPutQueue.push(operationStack.top());
        operationStack.pop();
    }

    while (!outPutQueue.empty()) {
        string token = outPutQueue.front();
        outPutQueue.pop();
        int i = 0;
        if (token != "-" && token.at(0) == '-'){
            i = 1;
        }
        if (isdigit(token.at(i))) {     //SCAT!
            operationStack.push(token);
        } else {
            string right = operationStack.top();

            operationStack.pop();
            if (operationStack.empty()) {
                left = "0";
            }
            else{
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